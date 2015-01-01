/****************************************************************************
 Copyright (c) 2013      cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "RootViewController.h"
#import "cocos2d.h"
#import "CCEAGLView.h"

@implementation RootViewController

/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}*/

- (GADRequest *)getGADRequest {
    GADRequest *request = [GADRequest request];
    request.testDevices = @[@"31dc7200c408120825a49d2c336921c7"];
    return request;
}

- (void)loadGADInterstitial {
    // 插页式广告
    interstitial_ = [[GADInterstitial alloc] init];
    interstitial_.adUnitID = @"ca-app-pub-5072970286349933/9504216029";
    interstitial_.delegate = self;
    [interstitial_ loadRequest:[self getGADRequest]];
}

- (void) addGameView
{
    // 在屏幕顶部创建标准尺寸的视图。
    // 在GADAdSize.h中对可用的AdSize常量进行说明。
    bannerView_ = [[GADBannerView alloc] initWithAdSize:kGADAdSizeBanner];
    
    // 指定广告单元ID。
    bannerView_.adUnitID = @"ca-app-pub-5072970286349933/8027482821";
    
    // 告知运行时文件，在将用户转至广告的展示位置之后恢复哪个UIViewController
    // 并将其添加至视图层级结构。
    bannerView_.rootViewController = self;
    [self.view addSubview:bannerView_];
    
    // 启动一般性请求并在其中加载广告。
    [bannerView_ loadRequest:[self getGADRequest]];
    
    // 插页式广告
    [self loadGADInterstitial];
}

// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskAllButUpsideDown;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
    [super didRotateFromInterfaceOrientation:fromInterfaceOrientation];

    cocos2d::GLView *glview = cocos2d::Director::getInstance()->getOpenGLView();

    if (glview)
    {
        CCEAGLView *eaglview = (CCEAGLView*) glview->getEAGLView();

        if (eaglview)
        {
            CGSize s = CGSizeMake([eaglview getWidth], [eaglview getHeight]);
            cocos2d::Application::getInstance()->applicationScreenSizeChanged((int) s.width, (int) s.height);
        }
    }
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];

    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}

- (void)showInterstitialAd {
    if ([interstitial_ isReady]) {
        [interstitial_ presentFromRootViewController:self];
    }
}

#pragma mark - GameCenter

- (void)gameCenterViewControllerDidFinish:(GKGameCenterViewController *)gameCenterViewController
{
    [self dismissViewControllerAnimated:YES completion:nil];
}

#pragma mark - Interstitial Delegate
- (void)interstitial:(GADInterstitial *)ad didFailToReceiveAdWithError:(GADRequestError *)error
{
    NSLog(@"Interstitial Ad Error: %@", [error localizedDescription]);
    [self loadGADInterstitial];
}

- (void)interstitialDidDismissScreen:(GADInterstitial *)ad
{
    [self loadGADInterstitial];
}

@end

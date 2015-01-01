#include "Util_iOS.h"
#import <GameKit/GameKit.h>
#import "RootViewController.h"

void Util_iOS::commentInAppStore()
{
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"itms-apps://itunes.apple.com/us/app/tun-shi-shu-zi/id953857266?l=zh&ls=1&mt=8"]];
}

void Util_iOS::showGameCenter()
{
    GKGameCenterViewController *gameCenterController = [[GKGameCenterViewController alloc] init];
    if (gameCenterController != nil)
    {
        RootViewController *vc = (RootViewController *)[[[UIApplication sharedApplication] keyWindow] rootViewController];
        gameCenterController.gameCenterDelegate = vc;
        [gameCenterController setViewState:GKGameCenterViewControllerStateAchievements];
        [vc presentViewController: gameCenterController animated: YES completion:nil];
    }
}

void Util_iOS::showActivities()
{
    NSString *str = NSLocalizedString(@"ShareString", nil);
    NSURL *url = [NSURL URLWithString:@"https://itunes.apple.com/us/app/tun-shi-shu-zi/id953857266?l=zh&ls=1&mt=8"];
    UIActivityViewController *avc = [[UIActivityViewController alloc] initWithActivityItems:@[str, url] applicationActivities:nil];
    RootViewController *vc = (RootViewController *)[[[UIApplication sharedApplication] keyWindow] rootViewController];
    [vc presentViewController:avc animated:YES completion:nil];
}

void Util_iOS::showInterstitialAd()
{
    RootViewController *vc = (RootViewController *)[[[UIApplication sharedApplication] keyWindow] rootViewController];
    [vc showInterstitialAd];
}

void Util_iOS::reportScore(int score)
{
    GKScore *scoreReporter = [[GKScore alloc] initWithLeaderboardIdentifier:@"EatNum_Score"];
    scoreReporter.value = score;
    scoreReporter.context = 0;
    
    NSArray *scores = @[scoreReporter];
    [GKScore reportScores:scores withCompletionHandler:^(NSError *error) {
        //Do something interesting here.
    }];
}

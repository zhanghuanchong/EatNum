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

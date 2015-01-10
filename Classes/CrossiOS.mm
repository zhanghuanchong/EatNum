#include "CrossiOS.h"
#include "Util.h"
#import <GameKit/GameKit.h>
#import <MessageUI/MessageUI.h>
#import "RootViewController.h"

void CrossiOS::commentInAppStore()
{
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"itms-apps://itunes.apple.com/us/app/tun-shi-shu-zi/id953857266?l=zh&ls=1&mt=8"]];
}

void CrossiOS::showGameCenter()
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

void CrossiOS::showActivities()
{
    NSString *str = NSLocalizedString(@"ShareString", nil);
    NSURL *url = [NSURL URLWithString:@"https://itunes.apple.com/us/app/tun-shi-shu-zi/id953857266?l=zh&ls=1&mt=8"];
    UIActivityViewController *avc = [[UIActivityViewController alloc] initWithActivityItems:@[str, url] applicationActivities:nil];
    RootViewController *vc = (RootViewController *)[[[UIApplication sharedApplication] keyWindow] rootViewController];
    [vc presentViewController:avc animated:YES completion:nil];
}

void CrossiOS::showInterstitialAd()
{
    RootViewController *vc = (RootViewController *)[[[UIApplication sharedApplication] keyWindow] rootViewController];
    [vc showInterstitialAd];
}

void CrossiOS::reportScore(int score)
{
    GKScore *scoreReporter = [[GKScore alloc] initWithLeaderboardIdentifier:@"EatNum_Score"];
    ValueVector v = U::getAllSkippedLevels();
    scoreReporter.value = score - v.size();
    scoreReporter.context = 0;
    
    NSArray *scores = @[scoreReporter];
    [GKScore reportScores:scores withCompletionHandler:^(NSError *error) {
        if (error != nil) {
            NSLog(@"Error in reporting score: %@", error);
        } else {
            NSLog(@"Reported score: %lli", scoreReporter.value);
        }
    }];
    
    if (score < 5) {
        return;
    }
    
    NSString *identifier = nil;
    NSMutableArray *achievements = [[NSMutableArray alloc] init];
    if (score == 5) {
        identifier = @"EatNum_Tutorial";
    } else if (score == 20) {
        identifier = @"Achievement_Level_1";
    } else if (score == 40) {
        identifier = @"Achievement_Level_2";
    } else if (score == 60) {
        identifier = @"Achievement_Level_3";
    } else if (score == 80) {
        identifier = @"Achievement_Level_4";
    } else if (score == 100) {
        identifier = @"Achievement_Level_5";
    } else if (score == 120) {
        identifier = @"Achievement_Level_6";
    } else if (score == 140) {
        identifier = @"Achievement_Level_7";
    } else if (score == 158) {
        identifier = @"Achievement_Level_8";
    }
    if (score > 5) {
        NSLog(@"Achievement: Achievement_Start");
        GKAchievement *achievement = [[GKAchievement alloc] initWithIdentifier: @"Achievement_Start"];
        if (achievement)
        {
            achievement.percentComplete = 100.0;
            achievement.showsCompletionBanner = YES;
            [achievements addObject:achievement];
        }
    }
    
    if (identifier != nil) {
        NSLog(@"Achievement: %@", identifier);
        GKAchievement *achievement = [[GKAchievement alloc] initWithIdentifier: identifier];
        if (achievement)
        {
            achievement.percentComplete = 100.0;
            achievement.showsCompletionBanner = YES;
            [achievements addObject:achievement];
        }
    }
    if ([achievements count] > 0) {
        [GKAchievement reportAchievements:achievements withCompletionHandler:^(NSError *error)
         {
             if (error != nil)
             {
                 NSLog(@"Error in reporting achievements: %@", error);
             }
         }];
    }
}

void CrossiOS::sendMail()
{
    RootViewController *vc = (RootViewController *)[[[UIApplication sharedApplication] keyWindow] rootViewController];
    
    MFMailComposeViewController *mailPicker = [[MFMailComposeViewController alloc] init];
    mailPicker.mailComposeDelegate = vc;
    
    [mailPicker setSubject: NSLocalizedString(@"MailSubject", @"")];
    
    NSArray *toRecipients = [NSArray arrayWithObject: @"support@wuruihong.com"];
    [mailPicker setToRecipients: toRecipients];
    [vc presentModalViewController: mailPicker animated:YES];
}

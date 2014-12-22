#include "Util_iOS.h"

void Util_iOS::commentInAppStore()
{
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"itms-apps://itunes.apple.com/us/app/tun-shi-shu-zi/id953857266?l=zh&ls=1&mt=8"]];
}

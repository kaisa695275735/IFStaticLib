//
//  TPMFaceTrackManager.h
//  FleaMarket
//
//  Created by lujunchen on 2017/8/22.
//  Copyright © 2017年 taobao.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "TPMFaceFeature.h"

@interface TPMFaceTrackManager : NSObject
- (void)startFaceTrack:(id)target;
- (void)stopFaceTrack:(id)target;
+ (instancetype)shareInstance;
+ (NSArray *)complementedForeheadPointsFromArray:(NSArray *)featurePoints;
+ (TPMFaceFeature *)trackFaceWithData:(unsigned char *)data width:(CGFloat)width height:(CGFloat)height andAngle:(int)angle;
@end

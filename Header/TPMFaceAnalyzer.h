//
//  TPMFaceAnalyzer.h
//  TPMFramework
//
//  Created by lujunchen on 2018/2/6.
//  Copyright © 2018年 lujun. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TPMFaceFeature.h"

typedef NS_ENUM(NSInteger,TPMFaceState) {
    TPMFaceNotFound,
    TPMFaceDetected,
    TPMFaceOpenMouse,
    TPMFaceBlinkEye,
    TPMFaceKiss,
    TPMFaceBlinkLeftEye,
    TPMFaceBlinkRightEye
};

@interface TPMFaceAnalyzer : NSObject
- (TPMFaceFeature *)pointToFaceFeature:(NSArray * )facePoints withImageSize:(CGSize)imageSize;
- (void)inputFaceFeature:(TPMFaceFeature *)feature;
- (BOOL)detectFaceState:(TPMFaceState)stateType;
- (void)clearFaceFeature;
+ (instancetype)shareInstance;
@end

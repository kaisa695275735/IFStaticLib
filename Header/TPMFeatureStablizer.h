//
//  TPMFeatureStablizer.h
//  FaceAlign
//
//  Created by dreamqian on 16/3/2.
//  Copyright © 2016年 dreamqian. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
@interface TPMFeatureStablizer : NSObject

//初始化函数
- (void)refreshWithImageSize:(CGSize)imageSize clearOld:(BOOL)clearOld;
- (void)refreshWithImageSize:(CGSize)imageSize clearOld:(BOOL)clearOld pointNum:(NSInteger)pointNum;
//- (NSMutableArray *)updateWithFeatureArray:(NSMutableArray *)featArray;
- (NSMutableArray *)updateWithFeatureArrayV2:(NSArray *)featArray;

- (NSMutableArray *)updateWithFeatureArrayV3:(NSArray *)featArray;

@end

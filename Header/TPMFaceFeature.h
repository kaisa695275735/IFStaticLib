//
//  TPMFaceFeature.h
//
//  Created by vigosschen on 16/6/10.
//
//

#import <UIKit/UIKit.h>


@class UIImage;

#define MaxFacePointCount         75

typedef NS_ENUM(NSInteger,FaceDetectorType) {
    FaceDetector_System = 0,
    FaceDetector_FacePP,
    FaceDetector_Youtu,
    FaceDetector_OpenCV
};

FOUNDATION_EXTERN CGPoint   pointSub(CGPoint pt1, CGPoint pt2);
FOUNDATION_EXTERN CGPoint   pointAdd(CGPoint pt1, CGPoint pt2);
FOUNDATION_EXTERN float     distanceFrom(CGPoint pt1, CGPoint pt2);
FOUNDATION_EXTERN CGPoint   midFrom(CGPoint point1,CGPoint point2);
FOUNDATION_EXTERN CGPoint   midOfPoints(NSArray* index,NSArray *array);

#ifndef FACERECT_STRUCT
#define FACERECT_STRUCT
struct FaceRect{
    int x, y, w, h;
    float confidence;
};
#endif

typedef struct _Rect {
    int x;
    int y;
    int w;
    int h;
} MRect;

@interface TPMFaceFeature : NSObject

@property (nonatomic, assign) CGSize imageSize;
@property (nonatomic, assign) CGRect bounds;
@property (nonatomic, assign) CGRect leBounds;
@property (nonatomic, assign) CGRect reBounds;
@property (nonatomic, assign) CGRect mouthBounds;

- (void)setF_Features:(float [MaxFacePointCount][2])points;
- (void)getF_Features:(float [MaxFacePointCount][2])points;
- (void)setScaleX:(CGFloat)scaleX scaleY:(CGFloat)scaleY;
- (void)updateImageSize:(CGSize)imageSize;
- (BOOL)correct;
- (TPMFaceFeature *)scaleFeatureSize:(CGSize)size;
- (TPMFaceFeature *)rotateFeature:(CGFloat)radian;

+ (CGRect)calcPointsBounds:(int [][2])points count:(NSInteger)count;
@end


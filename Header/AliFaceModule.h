#ifndef _ALI_FACE_MODULE_HEADER_
#define _ALI_FACE_MODULE_HEADER_


//亲爱的调用同学，以下每个接口的注释内容将大大节省您的调试时间，所以请仔细阅读，以帮助你分分钟完成接入。:)

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */



/* 
 【该函数只在整个算法启动前调一次】

 返回0表示调用成功。

 一个ios的调用示例：
 NSString *dataFilePath0 = [[NSBundle mainBundle] pathForResource:@"fdmodel" ofType:@"jpg"];
 string sFaceDataFilePath0 = [dataFilePath0 UTF8String];
 
 NSString *dataFilePath1 = [[NSBundle mainBundle] pathForResource:@"fa68_37v2_0308_5" ofType:@"jpg"];
 string sFaceDataFilePath1 = [dataFilePath1 UTF8String];
 
 //string sFaceDataFilePath2 = [dataFilePath2 UTF8String];
 
 NSString *dataFilePath3 = [[NSBundle mainBundle] pathForResource:@"ldClassifier" ofType:@"jpg"];
 string sFaceDataFilePath3 = [dataFilePath3 UTF8String];
 
 InitFaceModule(sFaceDataFilePath0.c_str(),
 sFaceDataFilePath1.c_str(),
 NULL,
 sFaceDataFilePath3.c_str() );
 
 这几个字符串的参数，就是表示  模型文件的路径。因为算法init的时候要去读模型文件。
 倒数第二个参数，之所以设置为NULL，是因为当前的版本没用到那个模型（不排除以后算法继续升级会用到）。

 注意，如果初始化失败，一般是文件路径不对 或者 没有成功读到文件。注意检查下app的文件系统access权限。
 */
int InitFaceModule(const char * pFDModelPathName, const char * pLDModelNormalPathName,
                   const char * pLDModelYawPathName, const char * pLDClassifierPathName);



/* 
 【该函数在刚init后必须调一次，之后只在横竖屏切换、或输入图像size和rotate改变时调用】

 返回0表示调用成功。

 w,h 分别表示图像宽、高。注意无论是否需要底层转正，这里输入的都是原始图像的宽高。
 angle支持0，90，180, 270。

  两种时候调用【一般情况下，你只会用到以下case（a）】：
（a）需要设置摄像头方向时，包括： “一开始的初始化” 以及 “当用户切换前后摄像头且导致采集图像方向变化时”
（b）上层陀螺仪检测到横竖屏切换时，即手机转动
 例如，如果（b）没变，而（a）变了（陀螺仪检测到手机动了），直接把陀螺仪信息告诉算法就行了。


  必须指定正确的angle角度，这个angle角度表示：需要底层在检测前做多少角度的旋转。
  ios手机上，手机顺指针转90度的横屏可以设置90, 手机逆时针转90度的横屏可以设置270。
  Android手机上，一般情况下（不考虑上述（b）所说的陀螺仪辅助的情况下），可直接根据camera API接口拿到的"摄像头安装角度"映射下得到angle值。Android手机的前后置摄像头的安装角度可以通过上层camera的API接口拿到（一般分别是270和90）。

  关于输入的angle。以下是两个概念：
 （1）输入图像方向（跟摄像头采集参数和安装角度相关）
 （2）人脸在图像中的方向（跟人脸动没动、手机动没动相关）。
 我们set的angle是（1）（2）综合的结果，也就是告诉算法检测前要不要旋转图像。
*/
int SetSizeAndAngle(int w, int h, int angle);




/*
 【该函数每帧都调用】

 返回值表示检测到的人脸个数（当前版本的库只提供1个人脸支持）。返回值<0 一般是参数错误等，返回值==0是没有检测到人脸。
 记得通过返回值check算法是否检测到人脸！！

 [IN]  unsigned char * pDataInYuv是：你的yuv图像的y通道的头地址。我们只需要y通道数据。

 [OUT]  int ** ppFaceRect： 这个是底层给你的输出值，会告诉你人脸框int数组的头地址（四个int数，依次是框左上角的x,y 和 框的宽，框的高）。
                    即你可以通过 *ppFaceRect拿到底层告诉你的数组头地址，所以上层要传进来的是二级指针ppFaceRect。
 [OUT]  int ** ppFaceLandmark：这个是底层给你的输出值，会告诉你人脸68个点的float数组的头地址。每个点有两个坐标值（x和y），所以对于68个点，你会拿到 68*2 个float，按顺序对应68个点。
                    即你可以通过 *ppFaceLandmark拿到底层告诉你的数组头地址，所以上层要传进来的是二级指针ppFaceLandmark。

 [IN]  bIfUseFaceDirectAsOutput 可默认设为false。简单理解就是，是否强制将输出坐标变成"始终是眼睛在上面，嘴巴在下面"，这就是“UseFaceDirectAsOutput”的意思。
                    若设为false，就是按照人脸在输入图像中的真实位置来（如果脸在图像里是横着的，那眼睛就在嘴边左边或右边）
                    为了使算法库与业务模块解耦合，建议这里设为false，即“输出坐标一定与输入图像相match”。


 注意：
 （1） *ppFaceRect 和 *ppFaceLandmark分别是：人脸框的数组（四个int数，依次是框左上角的x,y 和 框的宽，框的高）和68个点的数组。
      不需要上层分配内存。你读取_pFaceRect和_pFaceLandmark对应的输出结果就好（只读不写）。
 （2） 如果没有检测到人脸或者中途因参数错误（返回返回值<=0），ppFaceRect 和 ppFaceLandmark 所指向的内存会被置为NULL（防止上层访问无意义内存）!!!
      即此时 *ppFaceRect == NULL, *ppFaceLandmark == NULL。所以请先检查返回值再访问 *ppFaceRect 和 *ppFaceLandmark 所指向的数组们。


 c++的调用示例：
 int *             _pFaceRect;
 float *           _pFaceLandmark;
 int faceNum = DetectFaceAndLandmark((unsigned char * )loc, false, &_pFaceRect, &_pFaceLandmark);

 当你拿到68个点的坐标后，可参考发布包里面的"人脸关键点排列图.png"来了解每个点表示人脸上的哪个位置。

 */
int DetectFaceAndLandmark(unsigned char * pDataInYuv, bool bIfUseFaceDirectAsOutput, int ** ppFaceRect, float ** ppFaceLandmark);



/*
 【该函数只在最后不需要用到这个算法的时候再调用】

 它与上面的InitFaceModule接口是一对好基友，请保证他俩在整个算法生命周期前后成对出现，谢谢。如果不deinit会导致您的app有内存泄露。
 */
void DeinitFaceModule();




//文件结束
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif


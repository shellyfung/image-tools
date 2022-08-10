import cv2
import numpy as np

display = True

img = cv2.imread('E:/cmake/edgeDetection/images/01.bmp')

# if display:
#     cv2.imshow("img", img)
#     cv2.waitKey()

rows, cols, ch = img.shape

gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
# if display:
#     cv2.imshow("gray", gray)
#     cv2.waitKey()

# 边缘提取
edge = cv2.Canny(gray, 50, 100, apertureSize=3, L2gradient=True)
# if display:
#     cv2.imshow("edge", edge)
#     cv2.waitKey()

# 膨胀
# kernel = np.ones((3, 3), dtype=np.uint8)
# dilate = cv2.dilate(edge, kernel, 1)  # 1:迭代次数，也就是执行几次膨胀操作
# if display:
#     cv2.imshow("dilate", dilate)
#     cv2.waitKey()

# 闭运算
kernel = np.ones((3, 3), dtype=np.uint8)
# 有缺陷，填补缺陷
close = cv2.morphologyEx(edge, cv2.MORPH_CLOSE, kernel)
# if display:
#     cv2.imshow("close", close)
#     cv2.waitKey()

# 提取轮廓
'''
findContour()函数中有三个参数，第一个img是源图像，第二个model是轮廓检索模式，第三个method是轮廓逼近方法。输出等高线contours和层次结构hierarchy。
model:  cv2.RETR_EXTERNAL  仅检索极端的外部轮廓。 为所有轮廓设置了层次hierarchy[i][2] = hierarchy[i][3]=-1
        cv2.RETR_LIST  在不建立任何层次关系的情况下检索所有轮廓。
        cv2.RETR_CCOMP  检索所有轮廓并将其组织为两级层次结构。在顶层，组件具有外部边界；在第二层，有孔的边界。如果所连接零部件的孔内还有其他轮廓，则该轮廓仍将放置在顶层。
        cv2.RETR_TREE  检索所有轮廓，并重建嵌套轮廓的完整层次。
        cv2.RETR_FLOODFILL  输入图像也可以是32位的整型图像(CV_32SC1)
method：cv2.CHAIN_APPROX_NONE  存储所有的轮廓点，任何一个包含一两个点的子序列（不改变顺序索引的连续的）相邻。
        cv2.CHAIN_APPROX_SIMPLE  压缩水平，垂直和对角线段，仅保留其端点。 例如，一个直立的矩形轮廓编码有4个点。
        cv2.CHAIN_APPROX_TC89_L1 和 cv2.CHAIN_APPROX_TC89_KCOS 近似算法
'''
contours, hierarchy = cv2.findContours(
    close,
    cv2.RETR_TREE,
    cv2.CHAIN_APPROX_SIMPLE)

# if display:
#     # 绘制单个轮廓
#     # cnt = contours[50]
#     # cv2.drawContours(dst, [cnt], 0, (0, 0, 255), 1)
#
#     # 绘制轮廓 第三个参数是轮廓的索引（在绘制单个轮廓时有用。要绘制所有轮廓，请传递-1）
#     dst = np.ones(img.shape, dtype=np.uint8)
#     cv2.drawContours(dst, contours, -1, (0, 255, 0), 1)
#     cv2.imshow("dst", dst)
#     cv2.waitKey()
#
# 判断轮廓面积
# dst = np.ones(img.shape, dtype=np.uint8)
for i, cnt in enumerate(contours):
    area = cv2.contourArea(cnt)
    if area > 100:
        print(i, area)

        dst = img.copy()
        # 绘制轮廓
        # dst = np.ones(img.shape, dtype=np.uint8)
        # cv2.drawContours(dst, [cnt], 0, (0, 255, 0), 1)
        # cv2.imshow("dst", dst)
        # cv2.waitKey()

        # 绘制最小外接矩形
        # dst = np.ones(img.shape, dtype=np.uint8)
        rect = cv2.minAreaRect(cnt)
        cx, cy = np.int0(rect[0])
        width, height = rect[1]
        if max(width, height) / min(width, height) < 1.5:
            box = cv2.boxPoints(rect)

            # 画示意线
            start_x = int((box[0][0] + box[1][0]) * 0.5)
            start_y = int((box[0][1] + box[1][1]) * 0.5)
            end_x = int((box[2][0] + box[3][0]) * 0.5)
            end_y = int((box[2][1] + box[3][1]) * 0.5)
            start = (start_x, start_y)
            end = (end_x, end_y)
            cv2.line(dst, start, end, (0, 255, 0), 1)
            # 画轮廓
            box = np.int0(box)
            cv2.drawContours(dst, [box], 0, (0, 0, 255), 1)
            # 添加文字
            font = cv2.FONT_HERSHEY_SIMPLEX
            image = cv2.putText(
                dst, str(height), (cx, cy), font, 0.8, (0, 0, 255), 1)

            cv2.imshow("dst", dst)
            cv2.waitKey()

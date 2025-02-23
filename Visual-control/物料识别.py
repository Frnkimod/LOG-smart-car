import cv2
import numpy as np

t_x=312
t_y=198
t_r=150


# 视频文件路径
video_path = 'output.avi'  # 替换为你的视频文件路径

# 创建VideoCapture对象
cap = cv2.VideoCapture(video_path)

# 检查视频是否打开成功
if not cap.isOpened():
    print("Error: Could not open video.")
    exit()

# 循环直到视频结束
while True:
    # 读取视频的下一帧
    ret, frame = cap.read()


    # 如果正确读取帧，ret为True
    if not ret:
        print("Error: Could not read frame or end of video.")
        break


    # 转换为灰度图
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    # 应用高斯模糊
    blurred = cv2.GaussianBlur(gray, (9, 9), 1)
    dst = cv2.Canny(blurred,40,80)
    circles = cv2.HoughCircles(blurred, cv2.HOUGH_GRADIENT, 1, 20, param1=40, param2=30,
                               minRadius=50, maxRadius=480)
    if circles is not None:
        circles = np.round(circles[0, :]).astype("int")
        print(circles[0])
        # 确保只处理检测到的第一个圆（最显著的圆）
        (x, y, r) = circles[0]
        cv2.circle(frame, (x, y), r, (0, 255, 0), 4)
        cv2.rectangle(frame, (x - 5, y - 5), (x + 5, y + 5), (0, 128, 255), -1)

    # 滤波帧
    cv2.imshow("LV", dst)
    # 显示帧
    cv2.imshow('OUT', frame)


    # 按'q'键退出循环
    if cv2.waitKey(1) == ord('q'):
        break

# 释放VideoCapture对象
cap.release()
# 关闭所有OpenCV窗口
cv2.destroyAllWindows()
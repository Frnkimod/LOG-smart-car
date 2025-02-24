import cv2
import numpy as np

t_x=312
t_y=198
t_r=150
# 定义红色、绿色和蓝色的HSV范围
red_lower = np.array([0, 150, 150])
red_upper = np.array([10, 255, 255])
green_lower = np.array([60, 70, 50])
green_upper = np.array([80, 200, 255])
blue_lower = np.array([90, 50, 50])
blue_upper = np.array([130, 255, 255])


def calculate_color_ratio(image, lower_color, upper_color):
    hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
    mask = cv2.inRange(hsv, lower_color, upper_color)
    total_pixels = image.shape[0] * image.shape[1]
    color_pixels = cv2.countNonZero(mask)
    ratio = color_pixels / total_pixels
    return ratio
# 视频文件路径
video_path = 'output.avi'  # 替换为你的视频文件路径

# 创建VideoCapture对象
#cap = cv2.VideoCapture(video_path)
cap = cv2.VideoCapture(0)  # 打开默认摄像头
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
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
                               minRadius=50, maxRadius=200)

    if circles is not None:
        circles = np.round(circles[0, :]).astype("int")
        print(circles[0])
        # 确保只处理检测到的第一个圆（最显著的圆）
        (x, y, r) = circles[0]
        cv2.circle(frame, (x, y), r, (0, 255, 0), 4)
        cv2.rectangle(frame, (x - 5, y - 5), (x + 5, y + 5), (0, 128, 255), -1)

    blurred = cv2.GaussianBlur(frame, (9, 9), 1)

    # 计算颜色占比
    red_ratio = calculate_color_ratio(blurred, red_lower, red_upper)
    green_ratio = calculate_color_ratio(blurred, green_lower, green_upper)
    blue_ratio = calculate_color_ratio(blurred, blue_lower, blue_upper)
    max_pixels = max(red_ratio, green_ratio, blue_ratio)
    if max_pixels == red_ratio:
        dominant_color = 'Red'
    elif max_pixels == green_ratio:
        dominant_color = 'Green'
    else:
        dominant_color = 'Blue'
    print(dominant_color)
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
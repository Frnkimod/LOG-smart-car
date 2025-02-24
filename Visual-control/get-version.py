import cv2
import numpy as np
class Version:
    def __init__(self):
        """
        初始化摄像头边缘检测器。
        """
        self.cap = cv2.VideoCapture(0)  # 打开默认摄像头
        self.cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
        self.cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
        #self.cap.set(cv2.CAP_PROP_FPS, 120)
        self.frame=None
    # 鼠标回调函数
    def get_mouse_position(self,event, x, y, flags, param):
        if event == cv2.EVENT_MOUSEMOVE:
            # 获取鼠标所在位置的BGR值
            bgr_value = self.frame[y, x]
            # 将BGR值转换为HSV值
            hsv_value = cv2.cvtColor(np.uint8([[bgr_value]]), cv2.COLOR_BGR2HSV)[0][0]
            print(f"Mouse position: ({x}, {y}), HSV value: {hsv_value}")

    def get_line_pos(self,gray,hsv_img):

        # 应用高斯模糊
        blurred = cv2.bilateralFilter(gray, 0,     30,        30)  # 双边滤波

        # 使用Canny算法检测边缘
        # edges = cv2.Canny(blurred, 50, 300)

        # Sobel边缘检测
        sobel_x = cv2.Sobel(blurred, cv2.CV_64F, 1, 0, ksize=3)
        sobel_y = cv2.Sobel(blurred, cv2.CV_64F, 0, 1, ksize=3)
        edges = np.sqrt(sobel_x ** 2 + sobel_y ** 2).astype(np.uint8)

        # 非锐化掩模增强
        blur = cv2.GaussianBlur(blurred, (5, 5), 0)
        enhanced = cv2.addWeighted(blurred, 1.5, blur, -0.5, 0)

        # 使用霍夫变换检测直线
        # lines = cv2.HoughLinesP(edges, 1, np.pi / 180, threshold=100, lines=np.array([]), minLineLength=100,
        #                         maxLineGap=10)
        lines=None
        # 查找轮廓

        #contours, _ = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        return lines,edges,blurred

    def get_line_angle(self):
        ...

    def hough_circle(self,image, dp, minDist, param1, param2, minRadius, maxRadius):
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        dst = cv2.medianBlur(gray, 3)
        circles = cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT, dp, minDist, param1=param1, param2=param2,
                                   minRadius=minRadius, maxRadius=maxRadius)
        if circles is not None:
            circles = np.round(circles[0, :]).astype("int")
            # 确保只处理检测到的第一个圆（最显著的圆）
            (x, y, r) = circles[0]
            cv2.circle(image, (x, y), r, (0, 255, 0), 4)
            cv2.rectangle(image, (x - 5, y - 5), (x + 5, y + 5), (0, 128, 255), -1)
            return image, (x, y)
        else:
            return image, None
    def process_frame(self):
        """
        捕获视频帧并进行边缘检测。
        """
        while True:
            ret, self.frame = self.cap.read()  # 读取摄像头帧
            if not ret:
                print("无法读取摄像头数据")
                break

            #self.frame = cv2.imread('img/map1.png')  # 替换为你的图像路径

            # 将帧转换为灰度图像
            gray = cv2.cvtColor(self.frame, cv2.COLOR_BGR2GRAY)


            #lines,edge,blurred=self.get_line_pos(self.frame, self.frame)

            # # 在原始图像上绘制检测到的直线
            # if lines is not None:
            #     for line in lines:
            #         x1, y1, x2, y2 = line[0]
            #         cv2.line(self.frame, (x1, y1), (x2, y2), (0, 255, 0), 2)

            # 显示原始图像和边缘检测结果
            image, circles =self.hough_circle(self.frame, dp=1, minDist=400, param1=30, param2=90, minRadius=10, maxRadius=400)
            cv2.imshow('Original', self.frame)
            cv2.setMouseCallback('Original', self.get_mouse_position)

            #cv2.imshow('Edges', edge)

            # 按 'q' 键退出
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

    def release(self):
        """
        释放摄像头资源。
        """
        self.cap.release()
        cv2.destroyAllWindows()

class UART:
    def __init__(self,):
        ...

if __name__ == "__main__":
    uart = UART()
    version = Version()
    version.process_frame()

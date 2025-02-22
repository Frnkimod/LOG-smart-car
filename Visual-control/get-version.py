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
        self.cap.set(cv2.CAP_PROP_FPS, 60)
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
        # # 定义两种颜色的阈值范围（示例为红色和蓝色，需根据实际情况调整）
        # # 灰色阈值
        # lower_gray = np.array([90, 120, 70])
        # upper_gray = np.array([120, 70, 200])
        # mask_gray = cv2.inRange(hsv_img, lower_gray, upper_gray)
        #
        # # 黄色阈值
        # lower_yellow  = np.array([0, 17, 100])
        # upper_yellow = np.array([200, 50, 255])
        # mask_yellow  = cv2.inRange(hsv_img, lower_yellow, upper_yellow)
        #
        # # 边缘检测
        # edges_yellow = cv2.Canny(mask_yellow, 10, 150)
        # edges_gray = cv2.Canny(mask_gray, 10, 150)
        # # 合并边缘
        # edges = cv2.bitwise_or(edges_yellow, edges_gray)
        # 应用高斯模糊
        blurred = cv2.GaussianBlur(gray, (5, 5), 0)

        # 使用Canny算法检测边缘
        edges = cv2.Canny(blurred, 50, 150)
        # 使用霍夫变换检测直线
        lines = cv2.HoughLinesP(edges, 1, np.pi / 180, threshold=100, lines=np.array([]), minLineLength=100,
                                maxLineGap=10)
        # 查找轮廓
        contours, _ = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        return lines,contours

    def get_line_angle(self):
        ...

    def process_frame(self):
        """
        捕获视频帧并进行边缘检测。
        """
        while True:
            # ret, self.frame = self.cap.read()  # 读取摄像头帧
            # if not ret:
            #     print("无法读取摄像头数据")
            #     break

            # 将帧转换为灰度图像
            gray = cv2.cvtColor(self.frame, cv2.COLOR_BGR2GRAY)


            lines,edge=self.get_line_pos(gray, self.frame)

            # 在原始图像上绘制检测到的直线
            if lines is not None:
                for line in lines:
                    x1, y1, x2, y2 = line[0]
                    cv2.line(self.frame, (x1, y1), (x2, y2), (0, 255, 0), 2)

            # 显示原始图像和边缘检测结果
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

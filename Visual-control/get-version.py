import cv2
class Version:
    def __init__(self):
        """
        初始化摄像头边缘检测器。
        """
        self.cap = cv2.VideoCapture(2)  # 打开默认摄像头

    def process_frame(self):
        """
        捕获视频帧并进行边缘检测。
        """
        while True:
            ret, frame = self.cap.read()  # 读取摄像头帧
            if not ret:
                print("无法读取摄像头数据")
                break
            # 将帧转换为灰度图像
            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            # 应用 Canny 边缘检测
            edges = cv2.Canny(gray, 100, 200)

            # 显示原始图像和边缘检测结果
            cv2.imshow('Original', frame)
            cv2.imshow('Edges', edges)

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

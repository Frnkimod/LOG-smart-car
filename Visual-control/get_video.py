import cv2

# 设置视频的帧率（每秒帧数）和分辨率
fps = 60.0  # 每秒25帧
frame_width = 640  # 帧宽度
frame_height = 480  # 帧高度

# 定义视频编码器和输出文件名
fourcc = cv2.VideoWriter_fourcc(*'XVID')  # 编码器，XVID是一个常用的编码器
output_filename = 'output1.avi'  # 输出文件名

# 创建VideoWriter对象
out = cv2.VideoWriter(output_filename, fourcc, fps, (frame_width, frame_height))

# 检查VideoWriter是否成功创建
if not out.isOpened():
    print("Error: Could not create VideoWriter.")
    exit()

# 捕获视频（这里使用摄像头作为示例）
cap = cv2.VideoCapture(0)

while True:
    # 读取摄像头的一帧
    ret, frame = cap.read()

    # 如果正确读取帧，ret为True
    if not ret:
        print("Error: Could not read frame.")
        break

    # 将帧写入文件
    out.write(frame)

    # 显示帧
    cv2.imshow('frame', frame)

    # 按'q'键退出循环
    if cv2.waitKey(1) == ord('q'):
        break

# 释放资源
cap.release()
out.release()
cv2.destroyAllWindows()
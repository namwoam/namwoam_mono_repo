
# import the opencv library
import cv2
import numpy as np

# define a video capture object
vid = cv2.VideoCapture(0)

def getMask(frame, lower, upper):
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    colorLower = np.array(lower, np.uint8)
    colorUpper = np.array(upper, np.uint8)
    colorMask = cv2.inRange(hsv, colorLower, colorUpper)
    kernal = np.ones((5, 5), np.uint8)
    colorMask = cv2.dilate(colorMask, kernal)
    return colorMask


while(True):

    # Capture the video frame
    # by frame
    ret, frame = vid.read()
    redLow = getMask(frame, [0, 100, 20], [10, 255, 255])
    redHigh = getMask(frame, [160, 100, 20], [179, 255, 255])
    green = getMask(frame, [25, 52, 72], [102, 255, 255])
    blue = getMask(frame, [94, 80, 2], [120, 255, 255])

    colors = [(redLow, (0, 0, 255), "Red"),
              (redHigh, (0, 0, 255), "Red"),
              (green, (0, 255, 0), "Green"),
              (blue, (255, 0, 0), "Blue")]
    areaLowerBound = 20000
    lineThinkness = 2
    for mask, colorCode, colorName in colors:
        contours, hierarchy = cv2.findContours(
            mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        for pic, contour in enumerate(contours):
            area = cv2.contourArea(contour)
            if (area > areaLowerBound):
                x, y, w, h = cv2.boundingRect(contour)
                cv2.rectangle(frame, (x, y), (x+w, y+h),
                              colorCode, lineThinkness)
                cv2.putText(frame, colorName+" size= " + str(area), (x, y),
                            cv2.FONT_HERSHEY_SIMPLEX, 1.0, colorCode)
             # Display the resulting frame
    cv2.imshow('Video Stream', frame)

    # the 'q' button is set as the
    # quitting button you may use any
    # desired button of your choice
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# After the loop release the cap object
vid.release()
# Destroy all the windows
cv2.destroyAllWindows()

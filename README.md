# Object-Tracking-using-OpenCV-Computer-Vision-
- Undertook all the work of Image Processing done using OpenCV. I calculated the (X, Y) coordinates of   Shuttle (Object) in the 2-D frame using Background Subtraction method in OpenCV and then, using the   laws and formulas of Projectile Motion, extended the work in 2-D frame to 3-D frame by assuming the   trajectory of shuttle (object) and thereby moving the robot to prescribed calculated position obtained through   laws of trajectory using Projectile.
-  The object tracking was required to track the position of an object in 3-D Space for ABU-ROBOCON.
-  Using OpenCV. I calculated the (X, Y) coordinates of Shuttle (Object) in the 2-D frame using Background Subtraction method and then, using the laws and formulas of Projectile Motion, extended the work in 2-D frame to 3-D frame.
-  By assuming the trajectory of shuttle (object) and thereby moving the robot to prescribed calculated position obtained through laws of trajectory using Projectile, the robot can be moved to the prescribed location.
-  More detailed information can be obtained on the WebPage under "Projects" Page.

Method of Sequential Images: (Main logic)
-  Sequentially read two frames from camera feed or video.
-  Compare these two frames to see which pixels have changed between them.

Working and algorithm implementation:

-  Obtaining Difference image:
-  Main formula used = cv::absdiff(frame1.frame2,output)
-  First, we will get a difference image, then we will convert it to threshold image, then again to reduce the noise level, we will implement a BLUR funtion from inbuilt openCV library, to get a more clearer and enhanced image.
-  In our main code, we have this main while loop, from which i am starting to explain. Now, if we can see here, i created some boolean functions and some matrices which we will use later on.
-  Boolean functions are used for debug(d), tracking(t), esc to exit program, and pause(p) where it will infinitely go into the loop to pause the program and when pressed again, it will come out of that infinite loop and continue the program.
-  In this main while loop, we open up our main video feed. within this while loop, we have another while loop,  which tests the current frame position, against the total frame count of the video, and when the current frame count equals the total frame count, we know that we have reached the end of the video,ok so at this point, we can release the capture, and reopen the video and do it all over again, and that's how we get a repeating video and if i want my own webcam for this, instaed of video, firstly, i will move the captur.open(0) and move it's if function outside of the first main while loop, because we don't need to open the video feed, everytime it reaches the last frame.
-  Now, I am using here cv::absdiff function that I talked earlier which is used as background subtraction, between two frames.
-  It will ask for one frame(input), second frame(input) and another frame(output). What to know also is, the input frames, need to be the grayscale images. So, before i use my absdiff function, I am going to convert the frames to grayscale images using cv::CVtcolor using source frame, destination frame(initialized earler) and code COLOR_BGR2GRAY. Similarly, frame 2, converting to grayscale and all repeated things. Ready to use absdiff function.
-  Using absdiff function, outputting in 'Differnce image' , it will need a little thresholding using cv::threshold(diffimg,thresholdimg,SensitivityValue,255,ThreshBinary). using debufg mode, we will show a frame using cv::imshow("Diff Img",diffimg) also similarly a threshold image.
-  Now after doing this also, i was gettimg a noise in the frames of difference image and threshold image, like two instances of ball at the same time, so to reduce that noise, i used an inbuilt function in OpenCV, which is cv::BLUR(thresholdimg,thresholdimg,cv::size(BLUR SIZE,BLUR SIZE).
-  After that , a final threshold image formed removing noise and all, and hence showed in a new frame(Final Diff. Image).


-  Tracking of object:
-  Now, its time to use our tracking function, so that we can track this object.
-  So, to track our image, i have made a function, seacrh for movement, which is going to search for that little white space for the object. And, basically, what we do here is, find countours function, we draw bounding rectangle, we use centroid of bounding rectangle around the countour and find the middle of the object. We have also a drawing function, ewhich is going to draw some crosshairs telling us that  we are tracking an object at (X,Y).
-  Now, to our main function below,an if function
if(TrackingEnabled is true)
     { searchformovement(thresholimg,frame1) }
and then we just show it right here cv::imshow(frame1, frame1)
-  So, if all this goes well, we are able to track this object.


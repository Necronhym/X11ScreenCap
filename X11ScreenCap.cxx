#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
int main(int argc, char* argv[] )
	{


		cv::namedWindow( "Controll Window", cv::WINDOW_NORMAL);
		cv::resizeWindow("Controll Window", 1200, 600);
		//Screenshot
		Display* display = XOpenDisplay(NULL);;
		Screen *screen = XScreenOfDisplay(display, 0);
		Window root = DefaultRootWindow(display);
		int x=0, y=0;
		int w=WidthOfScreen(screen);
		int h=HeightOfScreen(screen);
		//X11 stuff:
		XImage* img;
		img = XGetImage(display, root, x, y, w, h, AllPlanes, ZPixmap);
		cv::Mat Screen;
		Screen = cv::Mat(h, w, CV_8UC4, img->data);
		//Video Writer:
		cv::VideoWriter video("Output.avi", CV_FOURCC('M','J','P','G'), 10, cv::Size(w,h));
		cv::Mat Out;
		while(true)
			{
				//GetScreenFrame:
				img = XGetImage(display, root, x, y, w, h, AllPlanes, ZPixmap);
				Screen = cv::Mat(h, w, CV_8UC4, img->data);
				//Convert to usable format:
				cvtColor(Screen, Out, CV_RGBA2RGB);
				cv::imshow( "Controll Window", Out);
				//Export Video:
				video.write(Out);
				//Clean memory:
				Out.release();
				Screen.release();
				XDestroyImage(img);

				//Stop on excape:
				char c = (char)cv::waitKey(30);
    				if( c == 27 )
					{
     						break;
					}
			}
		//Relese Video:
		video.release();
		//Destory windows:
		cv::destroyAllWindows();		
		return 0;
	}

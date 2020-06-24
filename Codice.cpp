#include <opencv2/opencv.hpp>
#include <iostream>

//namespace per utilizzare tutte le funzioni di OpenCV
using namespace cv;
using namespace std;


void createAlphaMat(Mat &mat)
{
	CV_Assert(mat.channels() == 4);
	for (int i = 0; i < mat.rows; ++i) {
		for (int j = 0; j < mat.cols; ++j) {
			Vec4b& bgra = mat.at<Vec4b>(i, j);
			bgra[0] = UCHAR_MAX; // Blue
			bgra[1] = saturate_cast<uchar>((float(mat.cols - j)) / ((float)mat.cols) * UCHAR_MAX); // Green
			bgra[2] = saturate_cast<uchar>((float(mat.rows - i)) / ((float)mat.rows) * UCHAR_MAX); // Red
			bgra[3] = saturate_cast<uchar>(0.5 * (bgra[1] + bgra[2])); // Alpha
		}
	}
}

int main()
{
	vector<int> compression_params;
	compression_params.push_back(3);
	compression_params.push_back(9);
	//Mat corrisponde alla matrice di pixel che forma l'immagine
	Mat img = imread("prova.jpg");
	//namedWindow() costruisce la finestra dove poi imshow() mostrerà l'immagine
	//namedWindow("image", WINDOW_NORMAL);
	imshow("Display window", img); // Show our image inside it.
	waitKey(2500);

	//Supponiamo di voler ottenere le dimensioni dell'immagine
	//Gli attributi rows e cols ci permettono di conoscere
	//il numero di righe e il numero di colonne dell'immagine

	cout << "Numero di righe dell'immagine: " << img.rows << endl;
	cout << "Numero di colonne dell'immagine: " << img.cols << endl;

	waitKey(2500);

	//Supponiamo di voler convertire l'immagine da RGB a Scala di Grigi
	//Usiamo la funzione cvtColor()

	Mat imgGray = img.clone();
	cvtColor(imgGray, imgGray, cv::COLOR_RGB2GRAY);

	namedWindow("Immagine Gray", WINDOW_AUTOSIZE);
	imshow("Immagine Gray", imgGray);

	//imwrite("copy.jpg", imgGray, compression_params);

	waitKey(2500);

	// Create mat with alpha channel
	Mat mat(480, 640, CV_8UC4);
	createAlphaMat(mat);

	try {
		imwrite("copyBW.png", imgGray, compression_params);
	}
	catch (runtime_error& ex) {
		fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
		return 1;
	}

	fprintf(stdout, "Saved png file with alpha data.\n");
	//waitKey(0);

	//Mat imgTest = img.clone();
	Mat imgTest = imread("copyBW.png");

	cvtColor(imgTest, imgTest, int code, int dstCn = 0)
	
	for (int y = 0; y < imgTest.rows; y++)
	{
		for (int x = 0; x < imgTest.cols; x++)
		{
			// get pixel
			Vec3b & color = imgTest.at<Vec3b>(y, x);

			// ... do something to the color ....
			if (color[0] == 0 && color[1] == 0 && color[2] == 0)
			{
				color[0] = 51;
				color[1] = 0;
				color[2] = 51;
				//cout << "Pixel Black :" << x << "," << y << endl;
			}
			else if (color[0] == color[1] && color[2] == color[1] && color[1] != 255)
			{
				//color[0] = 51;
				color[1] = 0;
				//color[2] = 51;
			}
			// set pixel
			imgTest.at<Vec3b>(Point(x,y)) = color;
			//if you copy value
		}
	}

	namedWindow("Immagine Test", WINDOW_AUTOSIZE);
	imshow("Immagine Test", imgTest);

	//imwrite("copy.jpg", imgGray, compression_params);

	waitKey(2500);

	// Create mat with alpha channel
	Mat mat1(480, 640, CV_8UC4);
	createAlphaMat(mat1);

	try {
		imwrite("copyMOD.png", imgTest, compression_params);
	}
	catch (runtime_error& ex) {
		fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
		return 1;
	}

	fprintf(stdout, "Saved png file with alpha data.\n");
	//waitKey(0);

	return 0;
}


/*
int main(int argc, char **argv)
{

	Mat image =
	//Apriamo l'immagire utilizzando imread()
	
	Mat immagineOriginale = imread(argv[1]);

	//Attraverso l'attributo data andiamo a verificare se l'immagine
	//è stata aperta correttamente
	if (immagineOriginale.data == NULL)
	{
		cerr << "Error open image" << endl;
		return(-1);
	}

	//namedWindow() costruisce la finestra dove poi imshow()
	//mostrerà l'immagine
	namedWindow("Immagine Originale", CV_WINDOW_AUTOSIZE);
	imshow("Immagine Originale", immagineOriginale);

	//Supponiamo che si voglia fare un resize dell'Immagine
	//Andiamo ad utilizzare la funzione resize()

	//Cloniamo prima l'immagine originale in un'altra matrice
	Mat immagineResize = immagineOriginale.clone();
	resize(immagineResize, immagineOriginale, Size(640, 480));

	namedWindow("Immagine Resize", CV_WINDOW_AUTOSIZE);
	imshow("Immagine Resize", immagineOriginale);

	//Supponiamo di voler ottenere le dimensioni dell'immagine
	//Gli attributi rows e cols ci permettono di conoscere
	//il numero di righe e il numero di colonne dell'immagine
	cout << "Numero di righe dell'immagine: " << immagineOriginale.rows << endl;
	cout << "Numero di colonne dell'immagine: " << immagineOriginale.cols << endl;

	//Supponiamo di voler convertire l'immagine da RGB a Scala di Grigi
	//Usiamo la funzione cvtColor()

	Mat immagineGray = immagineOriginale.clone();
	cvtColor(immagineGray, immagineGray, CV_BGR2GRAY);

	namedWindow("Immagine Gray", CV_WINDOW_AUTOSIZE);
	imshow("Immagine Gray", immagineGray);

	waitKey(0);
	return(0);
}
*/
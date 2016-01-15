#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <ctime>
#include <vector>
#include <thread>
#include <mutex>
using namespace std;
using namespace cv;

mutex cinLock, coutLock, nLock;
int n=1;

void SplitImageThread(const int tc) {
	string inName;
	int nt;
	while (true) {
		cinLock.lock();
		if (cin.eof()) {
			cinLock.unlock();
			break;
		}
		getline(cin, inName);
		cinLock.unlock();
		if (inName.empty()) continue;
		coutLock.lock();
		cout<<'['<<tc<<"] Processing "<<inName<<endl;
		coutLock.unlock();
		Mat img_in=imread(inName);
		Mat left=img_in(Rect(0, 0, img_in.cols/2, img_in.rows));
		Mat right=img_in(Rect(img_in.cols/2, 0, img_in.cols-img_in.cols/2, img_in.rows));
		nLock.lock();
		nt=n++;
		nLock.unlock();
		imwrite("left/"+to_string(nt)+".jpg", left);
		imwrite("right/"+to_string(nt)+".jpg", right);
	}
	coutLock.lock();
	cout<<'['<<tc<<"] Processing "<<inName<<endl;
	coutLock.unlock();
}


int main() {
	unsigned threadsCount=thread::hardware_concurrency();
	cout<<"Running with "<<threadsCount<<" threads"<<endl;
	vector<thread> threads;
	for (int i=0; i!=threadsCount; ++i)
		threads.emplace_back(SplitImageThread, i);
	for (auto &th:threads)
		th.join();
	cout<<"Elapsed time: "<<double(clock())/CLOCKS_PER_SEC<<endl;
	return 0;
}

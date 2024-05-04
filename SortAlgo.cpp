               //Ad-Soyad: Aya Khalifa      Öğrenci No: 1306220166  [Homework 4] 
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
using namespace std;


void generateRandomNumbers(const string& filename) {
    ofstream outFile(filename);

    if (!outFile) {
        cerr << "Error: Unable to open the file." << endl;
        return;
    }

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dis(1, 1000);

    for (int i = 0; i < 1000; ++i) {
        int randomNum = dis(gen);
        outFile << randomNum << endl;
    }

    outFile.close();

    cout << "Random numbers have been written to '" << filename << "'." << endl;
}

void selectionSort(fstream& file, vector<int>& numbers){

     for (int i = 0; i < 1000 - 1; i++){
        int min_pos = i;
            for( int j = i + 1; j < 1000; j++){
                if (numbers[j]< numbers[min_pos]){
                    min_pos = j;
                }
            }
         if (min_pos != i){
            int temp = numbers[i];
            numbers[i] = numbers[min_pos];
            numbers[min_pos] = temp;
         }   
    }

    // Reset file position and overwrite the file with sorted numbers
    file.clear();
    file.seekp(0);
    for (const int& n : numbers) {
        file << n << std::endl;
    }

}

void insertionSort (fstream& file, vector<int>& numbers){

     for (int i = 1; i < 1000 - 1; i++){
        int key = numbers[i];
        int j = i - 1;
        while(j >= 0 && numbers[j] > key){
            numbers[j + 1] = numbers[j];
            j = j - 1;
        }
        numbers[j + 1] = key;    
      }   

       // Reset file position and overwrite the file with sorted numbers
    file.clear();
    file.seekp(0);
    for (const int& n : numbers) {
        file << n << std::endl;
    }

}


void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(arr.size());
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i];
            i++;
        } else {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }

    while (i <= mid) {
        temp[k] = arr[i];
        i++;
        k++;
    }

    while (j <= right) {
        temp[k] = arr[j];
        j++;
        k++;
    }

    for (int s = left; s <= right; s++) {
        arr[s] = temp[s];
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int main() {
    fstream file("random_numbers.txt", ios::in | ios::out);
    if (!file.is_open()) {
       cerr << "Can't open the file." << endl;
        return 1;
    }
    vector<int> arr;
    int num;
    while (file >> num) {
        arr.push_back(num);
    }

    generateRandomNumbers("random_numbers.txt");
    int choice;
    cout<<"Choose a sorting algorithm: 1.insertion 2.selection 3.merge"<<endl;
    cin >> choice;

    // Declare variables outside of the switch statement
    chrono::steady_clock::time_point start, end;
    chrono::milliseconds duration;

    switch (choice) {
        case 1:
            // Measure the start time
            start = chrono::steady_clock::now();
            insertionSort(file, arr);
            file.close();
            // Measure the end time
            end = chrono::steady_clock::now();

            // Calculate the duration
            duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            cout << "Numbers sorted and updated in 'random_numbers.txt'." << endl;
            // Output the duration
            cout << "Time taken: " << duration.count() << " milliseconds" << endl;
            break;
        case 2:
            // Measure the start time
            start = chrono::steady_clock::now();
            selectionSort(file, arr);
            // Measure the end time
            file.close();
            end = chrono::steady_clock::now();

            // Calculate the duration
            duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            cout << "Numbers sorted and updated in 'random_numbers.txt'." << endl;
            // Output the duration
            cout << "Time taken: " << duration.count() << " milliseconds" << endl;
            break;
        case 3:
            // Measure the start time
            start = chrono::steady_clock::now();
            mergeSort(arr, 0, arr.size() - 1);

            for (int i = 0; i < arr.size(); i++) {
                file << arr[i] << endl;
            }
            file.close();

            // Measure the end time
            end = chrono::steady_clock::now();
            cout << "Sorting completed and saved to the file successfully." << endl;

            // Calculate the duration
            duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            cout << "Numbers sorted and updated in 'random_numbers.txt'." << endl;
            // Output the duration
            cout << "Time taken: " << duration.count() << " milliseconds" << endl;
            break;
        default:
            break;
    }
    return 0;
}

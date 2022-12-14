// C++ program to implement Second Chance Algorithm which is one of the LRU Approximation Page Replacement Algorithm

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void printOutput(int total_page_fault, int n);
void printFrames(int page, int no_of_frames, vector<pair<int, bool>> &frames);
int findAndReplace(int page, int no_of_frames, vector<pair<int, bool>> &frames, int pointer);
bool isNeedForUpdate(int page, int no_of_frames, vector<pair<int, bool>> &frames);
int applySecondChanceAlgo(vector<int> reference_string, int no_of_frames, vector<pair<int, bool>> frames);

int main()
{
    cout << fixed << setprecision(2);

    int i, n, no_of_frames, total_page_fault = 0;
    bool flag = false;

    // *********** INPUT **********
    cout << "\n**************** INPUT ***************\n";
    cout << "\nEnter the length of reference strings (no of pages):\n";
    cin >> n;

    // create reference string array
    vector<int> reference_string(n);
    cout << "\nEnter the reference string (actual page numbers) :\n";
    for (int i = 0; i < n; i++)
        cin >> reference_string[i];

    cout << "\nEnter the no. of frames you want to give to the process :\n";
    cin >> no_of_frames;

    // create frame vector. It stores (page no , reference bit) together
    vector<pair<int, bool>> frames(no_of_frames);

    // initialise the frames as page no = -1 , reference bit =0
    for (int i = 0; i < no_of_frames; i++)
    {
        frames[i].first = -1;
        frames[i].second = false;
    }

    cout << "\n**************** FRAMES ***************\n\n";

    total_page_fault = applySecondChanceAlgo(reference_string, no_of_frames, frames);

    // *********** OUTPUT **********
    printOutput(total_page_fault, n);

    return 0;
}

// Function to return the total Page faults
int applySecondChanceAlgo(vector<int> reference_string, int no_of_frames, vector<pair<int, bool>> frames)
{
    int total_page_fault = 0, pointer = 0;
    for (auto page : reference_string)
    {
        // check if there is need for Updating/replacing the page inside Frames vector
        if (isNeedForUpdate(page, no_of_frames, frames))
        {
            // if yes, then find the page in frames vector which need to be replaced and replace accordingly
            pointer = findAndReplace(page, no_of_frames, frames, pointer);
            // increase page fault count
            total_page_fault++;
        }

        // Print the content present inside frames
        printFrames(page, no_of_frames, frames);
    }
    // return total page faults to main()
    return total_page_fault;
}

// Function to check if there is need for Updating/replacing the page inside Frames vector
bool isNeedForUpdate(int page, int no_of_frames, vector<pair<int, bool>> &frames)
{
    // search the frames vector
    for (int i = 0; i < no_of_frames; i++)
    {
        if (frames[i].first == page) // page already exists in frame
        {
            frames[i].second = true; // update the reference bit = 1 for giving second chance in future
            return false;            // No need for Page replacement
        }
    }
    return true; // There is need for page replacement as page is not present already
}

// Function to find the victim page to be replaced and replace it accordingly by your new page
// It return the updated pointer of location from where the new search starts next time
int findAndReplace(int page, int no_of_frames, vector<pair<int, bool>> &frames, int pointer)
{
    while (true)
    {
        if (frames[pointer].second == 0)
        {
            // Replace i.e put your page at this pointed location in frames
            frames[pointer].first = page;
            pointer = (pointer + 1) % no_of_frames;
            return pointer;
        }
        // if reference bit = 1 , then give the second chance and make this bit = 0 again
        //  and proceed to next location to search
        frames[pointer].second = 0;
        pointer = (pointer + 1) % no_of_frames;
    }

    return pointer;
}

// Function to Print the Frames vector (only Page numbers are printed)
void printFrames(int page, int no_of_frames, vector<pair<int, bool>> &frames)
{
    cout << "page " << page << ": ";
    for (auto i : frames)
    {
        if (i.first == -1)
            continue;

        cout << i.first << "(" << i.second << ") ";
    }
    cout << endl;
}

// Function to Print the total number of Page Faults, Page Fault Ratio and Page Hit Ratio
void printOutput(int total_page_fault, int n)
{
    cout << "\n\n*********** OUTPUT **********\n";
    cout << "\nTotal No. of Page faults = " << total_page_fault;
    cout << "\nPage fault Ratio = " << (float)total_page_fault / n;
    cout << "\nPage Hit Ratio = " << (float)(n - total_page_fault) / n << "\n\n";
}
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
using namespace std;

void openMenu() {
    cout << "1. Input Text\n";
    cout << "2. Show Log\n";
    cout << "3. Update Status\n";
    cout << "4. Clear Screen\n";
    cout << "5. Menu\n";
    cout << "6. Exit\n";
}

enum Status {
    PENDING,
    ALMOST,
    COMPLETED
};

void statEnumToString(Status s) {
    switch (s) {
    case PENDING:
        cout << "PENDING\n";
        break;
    case ALMOST:
        cout << "ALMOST\n";
        break;
    case COMPLETED:
        cout << "COMPLETED\n";
        break;
    }
}

class Vec {
private:
    vector<string> v;
    vector<Status> status;

    int getSize() {
        return v.size();
    }

    void update(int index) {
        cout << "Update Status to:\n";
        cout << "0. PENDING\n";
        cout << "1. ALMOST\n";
        cout << "2. COMPLETED\n";

        int stat;
        cin >> stat;
        if (stat < 0 || stat > 2) cout << "Invalid Status\n";

        switch (stat) {
        case PENDING:
            cout << "Status Updated to PENDING\n";
            status[index] = PENDING;
            break;
        case ALMOST:
            cout << "Status Updated to ALMOST\n";
            status[index] = ALMOST;
            break;
        case COMPLETED:
            cout << "Status Updated to COMPLETED\n";
            v.erase(v.begin() + index);
            status.erase(status.begin() + index);
            break;
        }
    }

    void inputFile() {
		ifstream fin("SaveFile.txt");
        string tmp;

        while (getline(fin, tmp)) {
            v.emplace_back(tmp);
            status.emplace_back(PENDING);
        }

        fin.close();
    }

    void outputFile() {

        ofstream fout("SaveFile.txt");

        for (int i = 0; i < getSize(); i++) {
            fout << v[i] << "\n";
        }

		fout.close();
    }

    void clearAll() {
        v.clear();
    }

public:

    Vec() {
        inputFile();
    }

    ~Vec() {
        outputFile();
	}

    void addString(string s) {
        v.emplace_back(s);
        status.emplace_back(PENDING);
    }

    int currentSize() {
        return getSize();
    }

    void showLog() {
        for (int i = 0; i < getSize(); i++) {
            cout << i << ". " << v[i] << " ";
			statEnumToString(status[i]);
        }
    }

    void updateStatus() {
        cout << "Enter index to update status: ";
        int index;
        cin >> index;
        update(index);
    }

    void reset() {
        clearAll();
	}
};


int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    openMenu();

    Vec text;

    int inp;
    while (cin >> inp) {

        if (inp == 1) {
            string tmp;
            cin.ignore();

            getline(cin, tmp);
            text.addString(tmp);
        }

        else if (inp == 2) text.showLog();

        else if (inp == 3) {
            text.showLog();
            text.updateStatus();
        }

        else if (inp == 4) {
            system("CLS");
			openMenu();
        }

        else if (inp == 5) openMenu();

		else break;
    }

    return 0;
}


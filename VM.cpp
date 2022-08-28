#include "VM.h"

VM::VM(machineCodeGenerator* _machineCodeGnerator) {
    this->_machineCodeGnerator = _machineCodeGnerator;
    this->createDS();
    this->createMC();
}

void VM::createDS(){
    for (auto i : _machineCodeGnerator->symbolTable){
        pair<string , string> temp;
        temp.first = i.second.first;
        temp.second = i.second.second.second;
        ds[stoi(i.second.second.first)] = temp;
    }

    // cout << "Symbol Table: " << endl;
    // for(auto i : ds){
    //     cout << i.first << " " << i.second.first << " " << i.second.second << endl;
    // }
        
}

void VM::createMC(){
    ifstream read;
    read.open("mc.txt");
    
    this->mc = new int * [_machineCodeGnerator->totalLines];

    for(int i = 0; i < _machineCodeGnerator->totalLines; i++){
        mc[i] = new int[4];
        
        int temp;
        read >> temp;
        if(temp == 0 || temp == 1 || temp == 2 || temp == 3 || temp == 4 || temp == 5 || temp == 7 || temp == 8 || temp == 9 || temp == 10 || temp == 11){
            mc[i][0] = temp;
            read >> temp;
            mc[i][1] = temp;
            read >> temp;
            mc[i][2] = temp;
            read >> temp;
            mc[i][3] = temp;
        }
        else if(temp == 12 || temp == 13 || temp == 14 ||  temp == 15 ||  temp == 16){
            mc[i][0] = temp;
            read >> temp;
            mc[i][1] = temp;
            mc[i][2] = _machineCodeGnerator->negativeInfinity;
            mc[i][3] = _machineCodeGnerator->negativeInfinity;
        }
        else if(temp == 6){
            mc[i][0] = temp;
            read >> temp;
            mc[i][1] = temp;
            read >> temp;
            mc[i][2] = temp;
            mc[i][3] = _machineCodeGnerator->negativeInfinity;
        }
    }

    // cout << "MC: " << endl;
    //  for(int i = 0; i < _machineCodeGnerator->totalLines; i++){
    //      for(int j = 0; j < 4; j++){
    //          if(mc[i][j] != _machineCodeGnerator->negativeInfinity){
    //              cout << mc[i][j] << " ";
    //          }
    //      }
    //      cout << endl;
    //  }

}

char VM::readChar(int address){
    //return stoi(ds[address].second);
}

void VM::saveChar(int address, char value){

}

int VM::readInt(int address){
    return stoi(ds[address].second);
}

void VM::saveInt(int address, int value){
    ds[address].second = to_string(value);
}

string VM::readString(int address){
    return ds[address].second;
}

void VM::run() {
    int pc = 0;
    bool flag = true;


    while (flag) {
        if(mc[pc][0] == 0){
            int i = mc[pc][1];
            int j = mc[pc][2];
            int k = mc[pc][3];

            i = readInt(i);
            j = readInt(j);

            if(i == j){
                pc = k - 1;
                continue;
            }
        }
        else if(mc[pc][0] == 1){
            int i = mc[pc][1];
            int j = mc[pc][2];
            int k = mc[pc][3];

            i = readInt(i);
            j = readInt(j);

            if(i <= j){
                pc = k - 1;
                continue;
            }
        }
        else if(mc[pc][0] == 2){
            int i = mc[pc][1];
            int j = mc[pc][2];
            int k = mc[pc][3];

            i = readInt(i);
            j = readInt(j);

            if(i >= j){
                pc = k - 1;
                continue;
            }
        }
        else if(mc[pc][0] == 3){
            int i = mc[pc][1];
            int j = mc[pc][2];
            int k = mc[pc][3];

            i = readInt(i);
            j = readInt(j);

            if(i != j){
                pc = k - 1;
                continue;
            }

        }
        else if(mc[pc][0] == 4){
            int i = mc[pc][1];
            int j = mc[pc][2];
            int k = mc[pc][3];

            i = readInt(i);
            j = readInt(j);

            if(i > j){
                pc = k - 1;
                continue;
            }
        }
        else if(mc[pc][0] == 5){
            int i = mc[pc][1];
            int j = mc[pc][2];
            int k = mc[pc][3];

            i = readInt(i);
            j = readInt(j);

            if(i < j){
                pc = k - 1;
                continue;
            }
        }
        else if(mc[pc][0] == 6){
            int value =  readInt(mc[pc][1]);
            saveInt(mc[pc][2], value);
        }
        else if(mc[pc][0] == 7){
            int i = mc[pc][1];
            int j = mc[pc][2];
            int k = mc[pc][3];

            i = readInt(i);
            j = readInt(j);
            int result = i + j;
            saveInt(k, result); 
        }
        else if(mc[pc][0] == 8){
            int i = mc[pc][1];
            int j = mc[pc][2];
            int k = mc[pc][3];

            i = readInt(i);
            j = readInt(j);
            int result = i - j;
        }
        else if(mc[pc][0] == 9){
            int i = mc[pc][1];
            int j = mc[pc][2];
            int k = mc[pc][3];

            i = readInt(i);
            j = readInt(j);
            int result = i / j;
            saveInt(k, result); 
        }
        else if(mc[pc][0] == 10){
            int i = mc[pc][1];
            int j = mc[pc][2];
            int k = mc[pc][3];
            
            i = readInt(i);
            j = readInt(j);
            int result = i * j;
            saveInt(k, result); 
        }
        else if(mc[pc][0] == 11){
            int i = mc[pc][1];
            int j = mc[pc][2];
            int k = mc[pc][3];

            i = readInt(i);
            j = readInt(j);
            int result = i % j;
            saveInt(k, result); 
        }
        else if(mc[pc][0] == 12){
            pc = mc[pc][1];
            pc -= 1;
            continue;
        }
        else if(mc[pc][0] == 13){
            int inpi;
            cin >> inpi;

            saveInt(mc[pc][1], inpi);
        }
        else if(mc[pc][0] == 14){
            char inpc;
            cin >> inpc;
            
        }
        else if(mc[pc][0] == 15){
            auto it = ds.find(mc[pc][1]);
            if(it->second.first == "STRING"){
                for(int i = 1; i < it->second.second.length() - 2; i++){
                    if(it->second.second[i] == '\\' && it->second.second[i+1] == 'n'){
                        i++;
                        cout << endl;
                    }
                    else{
                        cout << it->second.second[i];
                    }
                }
            }
            else{
                cout << it->second.second;
            }
        }
        else if(mc[pc][0] == 16){
            break;
        }
        pc++;
        if (pc > _machineCodeGnerator->totalLines) {
            break;
        }
    }
}

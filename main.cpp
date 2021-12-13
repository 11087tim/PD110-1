#include <iostream>
#include <cmath>
using namespace std;

struct StoreFeature{
    int x_coordinate = 0;
    int y_coordinate = 0;
    int store_price = 0;
    int store_demand = 0;
    int building_cost = 0;
    int multi_replenish = 0;
};
struct LogisticFeature{
    int x_coordinate = 0;
    int y_coordinate = 0;
    int capacity = 0;
    int building_cost = 0;
};
struct StoresAllowcation{
    int fully_used = 0;  // 0 -> not used yet. 1 -> used
    int partially_used = 0;
    int allowcation[50] = {0};
};

struct Answer{
    int final_store_cnt = 0;
    int final_logistic_cnt = 0;
    int final_partial_used_store = 0;

};
void Greedy_algorithm(LogisticFeature *logistic_center, StoreFeature *stores, int *candidate_logistic,
                      StoresAllowcation *candidate_store, int condition[4], Answer &final_build_strategy);
int profit_calculator(int current_logistic_num, LogisticFeature logistic_center, StoreFeature *stores, StoresAllowcation *candidate_store,
                      StoresAllowcation **best_strategy_logistic, int condition[4]);

int main() {
    int condition[4] = {0};
    for(int i = 0; i < 4; i++)
        cin >> condition[i];

    LogisticFeature *logistic_center = new LogisticFeature[condition[0]];
    StoreFeature *stores = new StoreFeature[condition[1]];
    int *candidate_logistic = new int[condition[0]];
    StoresAllowcation *candidate_stores = new StoresAllowcation[condition[1]];


    for(int i = 0; i < condition[0]; i++){  // logistic coordination insert
        cin >> logistic_center[i].x_coordinate;
        cin >> logistic_center[i].y_coordinate;
        candidate_logistic[i] = 0;
    }
    for(int i = 0; i < condition[1]; i++){  // stores coordination insert
        cin >> stores[i].x_coordinate;
        cin >> stores[i].y_coordinate;
        //candidate_stores[i].id = i;
    }
    for(int i = 0; i < condition[1]; i++){  //
        cin >> stores[i].store_demand;
    }
    for(int i = 0; i < condition[1]; i++){
        cin >> stores[i].building_cost;
    }
    for(int i = 0; i < condition[1]; i++){
        cin >> stores[i].store_price;
    }
    for(int i = 0; i < condition[0]; i++){  // logistic coordination insert
        cin >> logistic_center[i].building_cost;
    }
    for(int i = 0; i < condition[0]; i++){  // logistic coordination insert
        cin >> logistic_center[i].capacity;
    }
    Answer final_build_strategy;
    Greedy_algorithm(logistic_center, stores, candidate_logistic, candidate_stores, condition, final_build_strategy);

    cout << final_build_strategy.final_logistic_cnt << ' ';
    int building_print_cnt = 0;
    if(final_build_strategy.final_logistic_cnt != 0) {

        for (int i = 0; i < condition[0]; i++) {
            if (candidate_logistic[i] == 1) {
                cout << i + 1;
                building_print_cnt++;
                if (building_print_cnt < final_build_strategy.final_logistic_cnt) {
                    cout << ' ';

                } else {
                    cout << endl;
                    break;
                }
            } else {
                if (building_print_cnt == final_build_strategy.final_logistic_cnt) {
                    cout << endl;
                    break;
                }
            }

        }
    }
    else {
        cout << endl;
    }
    int final_store_cnt = final_build_strategy.final_store_cnt + final_build_strategy.final_partial_used_store;
    cout << final_store_cnt << ' ';
    if(final_store_cnt != 0) {
        int store_print_cnt = 0;
        for (int i = 0; i < condition[1]; i++) {
            if (candidate_stores[i].fully_used == 1 || candidate_stores[i].partially_used == 1) {
                cout << i + 1;
                store_print_cnt += 1;
                if (store_print_cnt < final_store_cnt) {
                    cout << ' ';
                } else {
                    cout << endl;
                    break;
                }
            } else {
                if (store_print_cnt == final_store_cnt) {
                    cout << endl;
                }
            }

        }
        for (int i = 0; i < condition[1]; i++) {
            for (int j = 0; j < condition[0]; j++) {
                cout << candidate_stores[i].allowcation[j];
                if (j != condition[0] - 1) {
                    cout << ' ';
                } else
                    cout << endl;
            }
        }
    }
    else {
        cout << endl;
        for(int i = 0; i < condition[1]; i++){
            for(int j = 0; j < condition[0]; j++){
                cout << 0;
                if(j != condition[0] - 1){
                    cout << ' ';
                }
                else{
                    cout << endl;
                }
            }
        }
    }
    return 0;
}
void Greedy_algorithm(LogisticFeature *logistic_center, StoreFeature *stores, int *candidate_logistic,
                      StoresAllowcation *candidate_store, int condition[4], Answer &final_build_strategy){
    while(true){
        StoresAllowcation **best_strategy_logistic = new StoresAllowcation *[condition[0]];
        for (int j = 0; j < condition[0]; j++) {
            best_strategy_logistic[j] = new StoresAllowcation[condition[1]];
        }
        int best_center = 0;  // best center int this iteration
        int best_center_value = 0;  // how much can generate by the best_center

        for (int i = 0; i < condition[0]; i++) {
            if (candidate_logistic[i] != 1) {  // which logistic center is still not built or fulled
                int current_center_value = profit_calculator(i, logistic_center[i], stores, candidate_store,
                                                             best_strategy_logistic, condition) - logistic_center[i].building_cost;
                if(current_center_value > best_center_value){  // compare center's net income
                    best_center_value = current_center_value;
                    best_center = i;
                }
            } else
                continue;
        }
        if(best_center_value <= 0){  // max profit <= 0 -> end of strategy
            delete [] best_strategy_logistic;
            break;
        }
        candidate_logistic[best_center] = 1;  // max profit > 0 -> continue the iteration
        final_build_strategy.final_logistic_cnt++;
        for(int i = 0; i < condition[1]; i++){  // !!!
            if(condition[3] == 1) {  // single-center-replenish policy
                if (best_strategy_logistic[best_center][i].fully_used == 1) {
                    //cout <<  "here" << ' ' << i << endl;
                    candidate_store[i].fully_used = 1;
                    candidate_store[i].allowcation[best_center]  = best_strategy_logistic[best_center][i].allowcation[best_center];
                    final_build_strategy.final_store_cnt++;
                }
            }
            else{  // multi-center-replenish policy
                if(best_strategy_logistic[best_center][i].fully_used == 1){
                    if(best_strategy_logistic[best_center][i].allowcation[best_center] == stores[i].store_demand){
                        candidate_store[i].allowcation[best_center] = stores[i].store_demand;
                        candidate_store[i].fully_used = 1;
                        if(candidate_store[i].partially_used == 1) {
                            candidate_store[i].partially_used = 0;
                            final_build_strategy.final_partial_used_store--;
                            final_build_strategy.final_store_cnt++;
                        }
                        else{
                            final_build_strategy.final_store_cnt++;
                        }
                    }
                    else{
                        candidate_store[i].allowcation[best_center] = best_strategy_logistic[best_center][i].allowcation[best_center];
                        stores[i].store_demand -= best_strategy_logistic[best_center][i].allowcation[best_center];
                        stores[i].multi_replenish = 1;  // cost has been paid
                        final_build_strategy.final_partial_used_store++;
                        candidate_store[i].partially_used = 1;  // only partially used
                    }
                }

            }
        }
        delete [] best_strategy_logistic;
        //cout << final_build_strategy.final_store_cnt << " " << final_build_strategy.final_logistic_cnt << endl;
        if(final_build_strategy.final_logistic_cnt == condition[0] || final_build_strategy.final_store_cnt == condition[1])
            break;
    }

}
int profit_calculator(int current_logistic_num, LogisticFeature logistic_center, StoreFeature *stores,
                      StoresAllowcation *candidate_store, StoresAllowcation **best_strategy_logistic, int condition[4]){

    int k = logistic_center.capacity; // current center's capacity
    int accumulated_value = 0;
    int store_cnt = 0;
    StoresAllowcation *used_stores = new StoresAllowcation[condition[1]];

        while(true) {  // find best stores combination with current logistic center
            float max_cp_value = 0;  // how much net income can the other stores can generate
            int best_store = 0;  // pick the following store
            for (int i = 0; i < condition[1]; i++) {
                float cp_value = 0;
                if (used_stores[i].fully_used == 0 && candidate_store[i].fully_used == 0) {  // not used yet
                    float value = stores[i].store_price - condition[2] *   // (p - cd)
                                                        (abs(logistic_center.x_coordinate - stores[i].x_coordinate) +
                                                         abs(logistic_center.y_coordinate - stores[i].y_coordinate));
                    if (k > stores[i].store_demand) {  // capacity > demand
                        if(stores[i].multi_replenish == 0)
                            cp_value = (value * stores[i].store_demand - stores[i].building_cost) / stores[i].store_demand ;  // (p-cd)* x / deliver amount

                        else
                            cp_value = (value * stores[i].store_demand) / stores[i].store_demand;  // building cost is already paid

                    } else {  // k <= demand
                        if(stores[i].multi_replenish == 0)
                            cp_value = (value * k - stores[i].building_cost) / k;
                        else
                            cp_value = (value * k) / k;
                    }
                    if (max_cp_value < cp_value) {
                        max_cp_value = cp_value;
                        best_store = i;
                    }
                    if(max_cp_value == cp_value) {
                        if(stores[i].store_demand < stores[best_store].store_demand){
                            max_cp_value = cp_value;
                            best_store = i;
                        }
                        else{
                            continue;
                        }
                    }
                }
            }
            store_cnt++;
            if(store_cnt == condition[1]){
                break;
            }
            if (max_cp_value <= 0){ // end this round
                //cout << "hi" << endl;
                break;
            }
            if(k <= stores[best_store].store_demand){  // end this round
                used_stores[best_store].fully_used = 1;
                used_stores[best_store].allowcation[current_logistic_num] =  k;
                accumulated_value += max_cp_value * k;
                //cout << "exit" << endl;
                break;
            }

            else{  // continue this round
                used_stores[best_store].fully_used = 1;
                used_stores[best_store].allowcation[current_logistic_num] =  stores[best_store].store_demand;
                accumulated_value += max_cp_value * stores[best_store].store_demand;
                k -= stores[best_store].store_demand;
                //cout << "cont" << ' ' << best_store << ' ' << max_cp_value << endl;
                //cout << k << endl;
                continue;
            }

        }

    for(int i = 0; i < condition[1]; i++){  // output result
        if(used_stores[i].fully_used == 1){  // used
            best_strategy_logistic[current_logistic_num][i].fully_used = 1;
            best_strategy_logistic[current_logistic_num][i].allowcation[current_logistic_num] = used_stores[i].allowcation[current_logistic_num];
        }

    }
    delete [] used_stores;
    return accumulated_value;

}

#include <iostream>


int main(){
    int n;
    std::cin >> n;

    for(int i = 0 ; i <= 2*n; i++){
        std::cout << i;
        if(i < 2*n){
            std::cout << ", ";
        }
    }

    std::cout << std::endl;
};

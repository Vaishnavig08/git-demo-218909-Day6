#include<future>   //for async 
#include<iostream>
/* 
    A   B   C

    option1 : one after the other .
    (Single Thread technique)


    (Multi Threading)
    opetion2 : I will complete all tasks in such a way that I practically start all of them at the same time,
               but juggling them based on some criteria.

    (parallel execution)
    option3 : map number of task amongst number of available "workers
               - task should be non-overlapping
               -should not be dependent on each other
               - two people cannot end up wriiting on same thing

    (Asynchronus execution)
                :you start a task and then leave it and start another task
    option4 : Start a task , eithere  delgeate it to anther worker OR do it yourself after some time
               - If someone else is doing a task, monitor it, wait for their work
               to be done , take follow -up actions accordingly
 */



/* 
    2 tasks
    >Calculate factorial of 5
    >Calculate square of a number given bt the user
 */

int square(std::future<int>& ft){
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout<<"Hello from square. I have started my work."<<"\n";
    int number = ft.get();
    return number* number;
}


int factorial(int number){
    std::this_thread::sleep_for(std::chrono::seconds(3));
    if(number < 0){
        throw std::runtime_error("negative");
    }
    else if(number == 0 || number == 1){
        return 1;
    }
    else{
        return number*factorial(number-1);
    }

}

int main(){
    //step 1: make a promise to compiler for giving the required parameter
    // so please start the task 
    std::promise<int> pr;

    //step 2: A future linked to the promise
    std::future<int> ft = pr.get_future();

    /* Os ko bolo : launch square(if possible a new thread) */
    /* becoz you have made a promise so the task will be started */
    std::future<int> result_ft = std::async (std::launch::async, &square, std::ref(ft));
    /* here first parameter: how to launch it ; if not given os will decide
    second parameter: kisko launch krna hai(square is consumer) --> pass future wala parameter
     */
    /* since async : chup chap main will start factorial ; now here we have delay(if user gives input for sq in 2 sec
    then square will get printed) */
    
    int val = 0;
    std::cin >> val;

    std::cout<<factorial(5);              //main thread me hi hoga becoz we didnt make another thread

    // int val = 0;
    // std::cin >> val;               /* cutting and pasting before calling fact */
    pr.set_value(val);
    
    std::cout<<"Result of Factorial is : "<<result_ft.get();

}

/* 
    client - server aechiyechture
    





    future-promise model
        square calculation
        Main needs to delegate the task of square calculation
        ----> a new thread for Square 





 */
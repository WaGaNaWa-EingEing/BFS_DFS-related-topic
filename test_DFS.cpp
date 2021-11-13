#include <iostream>

class stack_data {

    public:
    int row;
    int colum;//maze array position
    stack_data * next; // linked_list_pointer
    stack_data(int i,int a,stack_data * before):row(i),colum(a),next(before){
    };

    int check(int i,int a){
        if (row == i && colum == a){
            return 1;
        }else{
            return 0;
        }
    }//check data

};
//stack_data class.

class stack {

    stack_data * top;

    public : 
    stack():top(NULL){};

    void push(int i,int a){

        if(top!=NULL){
            if(!(check_data(i,a))){
                stack_data *tmp = new stack_data(i,a,top);
                top = tmp;
            }  
        }else{
            stack_data *tmp = new stack_data(i,a,top);
            top = tmp;
        }
        
    };
    //if data isn't in the stack than push the new data.

    stack_data* pop(){
        stack_data * result = top->next;
        delete top;
        top = result;
        return top;
    }//pop data.

    int check_data(int i,int a){
        stack_data * tmp = top;
        while(tmp != NULL){
            if(tmp->check(i,a)){
                return 1;
            }
            tmp = tmp->next;
        }
        return 0;
    }//check the all data in stack
};

//stack class 

int check_zero(stack *visit,int **maze,int x,int y);

int find_way(stack *visit, stack *tmp,int ** maze,int x,int y);

int main(){
    std::cout << "Hello World" <<std::endl;

    std::cout << "input 5X6 maze (0 : road, 1:wall)" <<std::endl;

    int ** maze = new int*[5];
    int ptr = 0;

    for(int i=0;i<5;i++){
        maze[i] = new int[6];
    }

    for(int i=0;i<5;i++){
        std::cin >> maze[i][0] >> maze[i][1] >> maze[i][2] >> maze[i][3] >> maze[i][4] >> maze[i][5];
    }

    std::cout << std::endl;

    for(int i=0;i<5;i++){
        for(int a=0;a<6;a++){
            std::cout << maze[i][a] << " ";
        }
        std::cout << std::endl;
    }

    //input maze data in the arr maze.

    stack * visit = new stack();
    stack * tmp = new stack();

    int flag = find_way(visit,tmp,maze,0,0);
    //find the all path with DFS

    std::cout << flag << std::endl;
    

    return 0;
}

int find_way(stack *visit, stack *tmp,int ** maze,int x,int y){

    if(maze[x][y] == 0){//check if there is a path in arr x,y
        std::cout << std::endl;
        std::cout << " visit " << x << " " << y << std::endl;
        visit->push(x,y);//the stack for record visited node.
        tmp->push(x,y);//the stack for DFS

        int flag = check_zero(visit,maze,x,y); // find the next way.(up,down,left,right)

        switch (flag)
        {
        case 1:
            find_way(visit,tmp,maze,x-1,y);//move to next way.
            break;
        
        case 2:
            find_way(visit,tmp,maze,x,y-1);//move to next way.
            break;
        
        case 3:
            find_way(visit,tmp,maze,x+1,y);//move to next way.
            break;
        
        case 4:
            find_way(visit,tmp,maze,x,y+1);//move to next way.
            break;
        case 0: // path cann't find.
            std::cout << "path blocked in " << x << " " << y << " start back tarcking" << std::endl; 
            stack_data * ptr = tmp->pop();//back tracking start. pop the data in the DFS stack.

            if(ptr == NULL){
                std::cout << "end"<< std::endl;
                return 0;
            }
            find_way(visit,tmp,maze,ptr->row,ptr->colum);//move to poped data.
            break;  
        }
    }
};

int check_zero(stack *visit,int **maze,int x,int y){ // find way for next.
    if(x-1 >=0 && maze[x-1][y] == 0){
        if((visit->check_data(x-1,y)) != 1){
            return 1;
        }
    }
    if(y-1 >=0 && maze[x][y-1] == 0){
        if((visit->check_data(x,y-1)) != 1){
            return 2;
        }
    }
    if(x+1 <5 && maze[x+1][y] == 0){
        if((visit->check_data(x+1,y)) != 1){
            return 3;
        }
    }
    if(y+1 <6 && maze[x][y+1] == 0){
        if((visit->check_data(x,y+1)) != 1){
            return 4;
        }
    }else{
        return 0;
    }
};
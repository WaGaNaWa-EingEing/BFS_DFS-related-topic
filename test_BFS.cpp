#include <iostream>

class queue_data {

    public :

    int x;// maze x
    int y;// maze y
    queue_data * next; // linked list next

    queue_data(int x,int y):x(x),y(y),next(NULL){};

    bool check_data(int x,int y){
        if(this->x == x && this->y == y){
            return true;
        }else{
            return false;
        }
    }//check queue_data.


};
//queue data class

class queue {

    public :

    queue_data * head;//queue head.
    queue_data * tail;//queue tail.

    queue():head(NULL),tail(NULL){
    };

    void push(int x,int y){
        queue_data * tmp;

        if(head == NULL){
            tmp = new queue_data(x,y);
            head = tmp;
            tail = tmp;
        }else{
            tmp = new queue_data(x,y);
            tail->next = tmp;
            tail = tmp;
        }
    };//push data in queue.

    queue_data * pop(){
        queue_data * ptr;

        ptr = head;

        if(head != NULL){
            head = head->next;
        }

        return ptr;
    };//pop data in the queue.

    bool check_data(int x,int y){

        queue_data * ptr;

        ptr = head;

        while(ptr != NULL){
            if(ptr->check_data(x,y)){
                return true;
            }else{
                ptr = ptr->next;
            }
        }

        return false;

    };//check all data in the queue.
    
};

class maze_data{
    
    int x;
    int y;

    bool visit;
    
    public:

    maze_data * next;

    maze_data(int x,int y):x(x),y(y),visit(false),next(NULL){};

    void visit_d(){
        visit = true;
    }

    maze_data * find(int x,int y,maze_data * head){
        maze_data * ptr;

        ptr = head;

        while(ptr != NULL){
            if(ptr->x == x && ptr->y == y){
                return ptr;
            }else{
                ptr = ptr->next;
            }
        }

        return NULL;

    }

    bool check(){
        return visit;
    }

};//maze_data for saving way in maze.

int find_way(maze_data * data,queue *que,int ** maze,int x,int y){

    maze_data * ptr;

    if(maze[x][y] == 0){
        std::cout << std::endl;
        std::cout << " visit " << x << " " << y << std::endl;

        ptr = data->find(x,y,data);//find if maze x,y is in the maze_data.
        if(ptr != NULL){
            ptr->visit_d();//if it is than check it as visited.
        }
    }

    //if there is a way in nearest path in maze -> than push it in the queue.
    if(x-1 >=0 && maze[x-1][y] == 0){

        ptr = data->find(x-1,y,data);

        if(ptr !=NULL){
            if(!ptr->check()){
                que->push(x-1,y);//than push it in the queue.
            }
        }

    }
    if(y-1 >=0 && maze[x][y-1] == 0){

        ptr = data->find(x,y-1,data);

        if(ptr !=NULL){
            if(!ptr->check()){
                que->push(x,y-1);//than push it in the queue.
            }
        }
        
    }
    if(x+1 <5 && maze[x+1][y] == 0){

        ptr = data->find(x+1,y,data);

        if(ptr !=NULL){
            if(!ptr->check()){
                que->push(x+1,y);//than push it in the queue.
            }
        }

        
    }
    if(y+1 <6 && maze[x][y+1] == 0){

        ptr = data->find(x,y+1,data);

        if(ptr !=NULL){
            if(!ptr->check()){
                que->push(x,y+1);//than push it in the queue.
            }
        }

    }

    queue_data * next_data = que->pop();//than pop the queue. 

    if(next_data != NULL){
        find_way(data,que,maze,next_data->x,next_data->y);//if there is a data in queue -> move there.
    }else{
        std::cout << " BFS End " << std::endl;//if queue is empty -> finish.
    }

};

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

    std::cout << std::endl;//input data in the maze.

    maze_data * head = NULL; //maze_data linked list head.
    maze_data * tmp;

    for(int i=0;i<5;i++){
        for(int a=0;a<6;a++){

            if(maze[i][a] == 0){
                if(head == NULL){
                    head = new maze_data(i,a);
                    tmp = head;
                }else{
                    tmp->next = new maze_data(i,a);
                    tmp = tmp->next;
                }
            }//if there is a way in maze -> than record it in maze_data_linked_list. 
            std::cout << maze[i][a] << " ";
        }
        std::cout << std::endl;
    }

    queue * que = new queue();//make new queue

    find_way(head,que,maze,0,0); // start with maze 0,0 and find path with BFS.

    return 0;
}
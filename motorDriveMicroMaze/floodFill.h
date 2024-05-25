



// function to check the if the neighbors are valid or not.(Neighbors should be in the boundaries of the maze. 16x16)
bool neighborCheck( int m, int n, int x, int y)
{
    if (x < 0 || x >=m || y < 0 || y >=n)
        return false;
    return true;
}

int floodFill(neighbors arr[][8] ,int m, int n, int x, int y)
{
    
    // cppQueue<pair<int, int> > queue;
   
    pair p={x, y};
    cppQueue queue(sizeof(p),255,FIFO);
    queue.push(&p);
    queue.pull(&p);
   
    arr[x][y].data = 0;
    arr[x][y].visited =1;
    Serial.println(p.first);
    while (queue.isEmpty() != 1) {

        // Dequeue the front node
        pair currPixel;
        queue.pop(&currPixel);
        
        int posX = currPixel.first;
        int posY = currPixel.second;
            
        
    
        if ((arr[posX][posY].SouthN==1) && (arr[posX-1][posY].visited==0)){
            Serial.println("if south");
            
            arr[posX - 1][posY].data = arr[posX][posY].data+1;
            
            
            p.first = posX - 1;
            p.second = posY;
            arr[posX - 1][posY].visited =1 ;
            queue.push(&p);
            
        }
 
        if ((arr[posX][posY].NorthN==1 && arr[posX+1][posY].visited==0)) {
            Serial.println("if north");
            
            arr[posX + 1][posY].data = arr[posX][posY].data+1;
             
            p.first = posX + 1;
            p.second = posY;
            arr[posX +1][posY].visited=1;
            queue.push(&p);
         
        }
 
        if( (arr[posX][posY].EastN==1 && arr[posX][posY+1].visited==0)) {
            Serial.println("if east");
            
            arr[posX][posY + 1].data = arr[posX][posY].data+1;
             
            p.first = posX;
            p.second = posY + 1;
            arr[posX][posY+1].visited=1;
            queue.push(&p);
        }
 
        if( (arr[posX][posY].WestN==1 && arr[posX][posY-1].visited==0) ){
            Serial.println("if west");
            
            arr[posX][posY - 1].data = arr[posX][posY].data+1;
             
            p.first = posX;
            p.second = posY - 1;
            arr[posX][posY-1].visited=1;
            queue.push(&p);
            
        }
    }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                arr[i][j].visited=0;
        }
        
    }
return (0);
}
// void wallsInit(neighbors microMouseSim[][16])
// //Initializing the walls - which we will be receiving from the Mouse in real time. 
// {
    

//     microMouseSim[0][1].SouthN=0;
//     microMouseSim[0][2].SouthN=0;
//     microMouseSim[0][3].SouthN=0;
//     microMouseSim[0][3].EastN=0;
//     microMouseSim[0][4].WestN=0;
//     microMouseSim[0][5].SouthN=0;
//     microMouseSim[0][6].SouthN=0;
    
//     microMouseSim[1][0].SouthN=0;
//     microMouseSim[1][1].SouthN=0;
//     microMouseSim[1][1].NorthN =0;
//     microMouseSim[1][2].SouthN=0;
//     microMouseSim[1][2].NorthN =0;
//     microMouseSim[1][3].NorthN =0;
//     microMouseSim[1][4].EastN =0;
//     microMouseSim[1][5].WestN =0;
//     microMouseSim[1][5].NorthN =0;
//     microMouseSim[1][6].EastN =0;
//     microMouseSim[1][6].NorthN =0;
//     microMouseSim[1][7].WestN =0;

//     microMouseSim[2][0].SouthN=0;
//     microMouseSim[2][0].NorthN=0;
//     microMouseSim[2][1].SouthN=0;
//     microMouseSim[2][1].NorthN =0;
//     microMouseSim[2][2].NorthN =0;
//     microMouseSim[2][3].EastN =0;
//     microMouseSim[2][4].WestN =0;
//     microMouseSim[2][4].SouthN =0;
//     microMouseSim[2][5].EastN =0;
//     microMouseSim[2][5].SouthN =0;
//     microMouseSim[2][6].WestN =0;

    
//     microMouseSim[3][0].NorthN=0;
//     microMouseSim[3][1].EastN=0;
//     microMouseSim[3][1].NorthN =0;
//     microMouseSim[3][2].WestN=0;
//     microMouseSim[3][2].EastN=0;
//     microMouseSim[3][3].WestN =0;
//     microMouseSim[3][4].NorthN =0;
//     microMouseSim[3][4].SouthN =0;
//     microMouseSim[3][5].NorthN =0;
//     microMouseSim[3][5].SouthN =0;
//     microMouseSim[3][6].EastN =0;
//     microMouseSim[3][7].WestN =0;
//     microMouseSim[3][7].SouthN =0;

//     microMouseSim[4][0].EastN=0;
//     microMouseSim[4][1].EastN=0;
//     microMouseSim[4][1].WestN =0;
//     microMouseSim[4][2].WestN=0;
//     microMouseSim[4][2].EastN=0;
//     microMouseSim[4][3].WestN =0;
//     microMouseSim[4][3].EastN =0;
//     microMouseSim[4][4].WestN =0;
//     microMouseSim[4][4].SouthN =0;
//     microMouseSim[4][4].NorthN =0;
//     microMouseSim[4][5].NorthN =0;
//     microMouseSim[4][5].SouthN =0;
//     microMouseSim[4][7].NorthN =0;
//     microMouseSim[4][7].SouthN =0;

//     microMouseSim[5][0].EastN=0;
//     microMouseSim[5][1].EastN=0;
//     microMouseSim[5][1].WestN =0;
//     microMouseSim[5][2].WestN=0;
//     microMouseSim[5][2].EastN=0;
//     microMouseSim[5][2].SouthN=0;
//     microMouseSim[5][3].WestN =0;
//     microMouseSim[5][4].NorthN =0;
//     microMouseSim[5][5].NorthN =0;
//     microMouseSim[5][5].SouthN =0;
//     microMouseSim[5][5].EastN =0;
//     microMouseSim[5][6].EastN =0;
//     microMouseSim[5][6].WestN =0;
//     microMouseSim[5][7].NorthN =0;
//     microMouseSim[5][7].WestN =0;

//     microMouseSim[6][0].EastN=0;
//     microMouseSim[6][1].WestN=0;
//     microMouseSim[6][2].NorthN=0;
//     microMouseSim[6][2].SouthN=0;
//     microMouseSim[6][3].EastN =0;
//     microMouseSim[6][3].SouthN =0;
//     microMouseSim[6][4].WestN =0;
//     microMouseSim[6][4].EastN =0;
//     microMouseSim[6][5].NorthN =0;
//     microMouseSim[6][5].WestN =0;
//     microMouseSim[6][6].EastN =0;
//     microMouseSim[6][6].SouthN =0;
//     microMouseSim[6][7].WestN =0;

//     microMouseSim[7][0].EastN=0;
//     microMouseSim[7][1].WestN=0;
//     microMouseSim[7][1].EastN=0;
//     microMouseSim[7][2].NorthN=0;
//     microMouseSim[7][2].WestN=0;
//     microMouseSim[7][3].NorthN =0;
//     microMouseSim[7][4].EastN =0;
//     microMouseSim[7][5].EastN =0;
//     microMouseSim[7][5].WestN =0;
//     microMouseSim[7][6].NorthN =0;
//     microMouseSim[7][6].WestN =0;
        

// }

void bubbleSort(neighbors arr[], short int n)
{
    short int i, j;
    bool swapped;
    neighbors temp;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j].data > arr[j + 1].data) {
                temp=arr[j];
                arr[j]=arr[j + 1];
                arr[j+1]=temp;
                swapped = true;
            }
        }

        // If no two elements were swapped
        // by inner loop, then break
        if (swapped == false)
            break;
    }
}

coordinates getShiftedNeighbours(){
  coordinates temp_coord= {1};
  if(setPointAngle == 0){
    temp_coord.northPresent = !irReadRF;
    temp_coord.eastPresent = !irReadRS;
    temp_coord.westPresent = !irReadLS;
    temp_coord.southPresent = !0;
  }
  else if(setPointAngle == 90){
    temp_coord.northPresent = !irReadLS;
    temp_coord.eastPresent = !irReadRF;
    temp_coord.westPresent = !0;
    temp_coord.southPresent = !irReadRS;
  }
  else if(setPointAngle == 180 || setPointAngle == -180){
    temp_coord.northPresent = !0;
    temp_coord.eastPresent = !irReadLS;
    temp_coord.westPresent = !irReadRS;
    temp_coord.southPresent = !irReadRF;
  }
  else if(setPointAngle == -90){
    temp_coord.northPresent = !irReadRS;
    temp_coord.eastPresent = !0;
    temp_coord.westPresent = !irReadRF;
    temp_coord.southPresent = !irReadLS;
  }
}

void init_flood(){
   // main array
  // static neighbors microMouseSim[8][8]={0};  // only for simulating the walls.
 
  // initializing Neighbors

     for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
        {
            if (neighborCheck(m, n, i - 1, j))
                arr[i][j].SouthN=1;
            if (neighborCheck(m, n, i + 1, j))
                arr[i][j].NorthN=1;
            if (neighborCheck(m, n, i , j+1))
                arr[i][j].EastN=1;
            if (neighborCheck(m, n, i , j - 1))
                arr[i][j].WestN=1;
        }
     }
     // copying the neighbors data to the Simulation array.
    // for (int i = 0; i < m; i++) {
    //     for (int j = 0; j < n; j++)
    //     { 
    //         microMouseSim[i][j].NorthN=arr[i][j].NorthN;
    //         microMouseSim[i][j].SouthN=arr[i][j].SouthN;
    //         microMouseSim[i][j].EastN=arr[i][j].EastN;
    //         microMouseSim[i][j].WestN=arr[i][j].WestN;
    
    //      }

    // }
    // wallsInit(microMouseSim);
  // Serial.print(" ");
  // Serial.println(nextCell.second);
    floodFill(arr, m, n, endingCell.first, endingCell.second);  //First init of FloodFill
}

pair main_flood(pair currCell){
  // neighbors arr[8][8]={0}; // main array
  // neighbors microMouseSim[8][8]={0};  // only for simulating the walls.
    // printarr(arr,m,n);
  neighbors temp[]={ {0,0,0,0,0,99,0,0},
                    {0,0,0,0,0,99,0,0},
                    {0,0,0,0,0,99,0,0},
                    {0,0,0,0,0,99,0,0}};
    coordinates temp1_coordinates = getShiftedNeighbours();
    // Serial.print(temp1_coordinates.eastPresent);
    // Serial.print(" ");
    // Serial.print(temp1_coordinates.westPresent);
    // Serial.print(" ");
    // Serial.print(temp1_coordinates.northPresent);
    // Serial.print(" ");
    // Serial.println(temp1_coordinates.southPresent);

        // arr[currCell.first][currCell.second].visitedMouse=1;
        arr[currCell.first][currCell.second].EastN=temp1_coordinates.eastPresent;
        arr[currCell.first][currCell.second+1].WestN=temp1_coordinates.eastPresent;

        arr[currCell.first][currCell.second].WestN=temp1_coordinates.westPresent;
        arr[currCell.first][currCell.second-1].EastN=temp1_coordinates.westPresent;
        
        arr[currCell.first][currCell.second].NorthN=temp1_coordinates.northPresent;
        arr[currCell.first+1][currCell.second].SouthN=temp1_coordinates.northPresent;
        
        arr[currCell.first][currCell.second].SouthN=temp1_coordinates.southPresent;
        arr[currCell.first-1][currCell.second].NorthN=temp1_coordinates.southPresent;
        
        // cout<<"Iteration: "<<k<<" #####################################"<<endl;
        // cout<<endl;
    
        floodFill(arr, m, n, endingCell.first, endingCell.second); 

        // printarr(arr,m,n);
        if (arr[currCell.first][currCell.second].NorthN +arr[currCell.first][currCell.second].SouthN+arr[currCell.first][currCell.second].EastN+arr[currCell.first][currCell.second].WestN<2)
        {
              if (arr[currCell.first][currCell.second].NorthN==1)
            {  nextCell.first=currCell.first+1;
                nextCell.second=currCell.second;
            }
              if (arr[currCell.first][currCell.second].SouthN==1)
            {  nextCell.first=currCell.first-1;
                nextCell.second=currCell.second;
            }
              if (arr[currCell.first][currCell.second].EastN==1)
            {  nextCell.first=currCell.first;
                nextCell.second=currCell.second+1;
            }
              if (arr[currCell.first][currCell.second].WestN==1)
            {  nextCell.first=currCell.first;
                nextCell.second=currCell.second-1;
            }
                  
        }

        else
        {
            if(arr[currCell.first][currCell.second].NorthN==1)
            {
              arr[currCell.first+1][currCell.second].PosX= currCell.first+1;
              arr[currCell.first+1][currCell.second].PosY= currCell.second;
              temp[0]=arr[currCell.first-1][currCell.second];

            }
            if(arr[currCell.first][currCell.second].SouthN==1)
            {
              arr[currCell.first-1][currCell.second].PosX= currCell.first-1;
              arr[currCell.first-1][currCell.second].PosY= currCell.second;
              temp[1]=arr[currCell.first+1][currCell.second];

            }
            if(arr[currCell.first][currCell.second].EastN==1)
            {
              arr[currCell.first][currCell.second+1].PosX= currCell.first;
              arr[currCell.first][currCell.second+1].PosY= currCell.second+1;
              temp[2]=arr[currCell.first][currCell.second+1];

            }
            if(arr[currCell.first][currCell.second].WestN==1)
            {
              arr[currCell.first][currCell.second-1].PosX= currCell.first;
              arr[currCell.first][currCell.second-1].PosY= currCell.second-1;
              temp[3]=arr[currCell.first][currCell.second-1];

            }
        
        bubbleSort(temp,sizeof(temp) / sizeof(temp[0]));
        nextCell.first=temp[0].PosX;
        nextCell.second=temp[0].PosY;
        

      

  }
    // if we have reached centre, break.
  
    if(arr[currCell.first][currCell.second].data==0) 
    {
          //cout<<"Destination Reached"<<endl;
          if (firstTime==true)
          {
            //cout<<"Going back to start Point"<<endl;
            
            endingCell.first=startingCell.first;
            endingCell.second=startingCell.second;
            for (int i = 0; i < m; i++) 
            {
                for (int j = 0; j < n; j++)
                      {  arr[i][j].data=0;
                        
                      } 
            }
            firstTime=false;
          return(currCell);
          }
          achieved_back_to_square_0 = 1;//##########################################//
      
    }
    if (firstTime==false)
    {
      if(pathStack.sizeOf() == 0)
          {
            pathStack.push(&currCell);
            
          }
      else{
            pathStack.peek(&xy);
            if(xy.first==nextCell.first && xy.second == nextCell.second)
            {  pathStack.pop(&xy);
            
            }
            else
            {
              pathStack.push(&currCell);
              
            }
      
      }
      
    }
    
    //cout<<"Next Cell:"<<nextCell.first<<" "<<nextCell.second<<endl;

    return(nextCell);
        
  }
    
    //cout<<"Flood Fill execution completed"<<endl;
    //  while (!pathStack.empty()) {
    //    pathCell=pathStack.top();
    //     //cout <<"("<<pathCell.first<<","<<pathCell.second<<")"<<endl;
    //     pathStack.pop();
    // }
    

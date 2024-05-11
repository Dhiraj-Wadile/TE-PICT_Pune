#include <stdio.h>

//Prototypes
void fifo(int frameSize,int ref[],int n);
void table(int frameSize,int refSize,int hitFlag[],int frame[][refSize]);
void LRU(int frameSize,int ref[],int n);
void optimal(int frameSize,int ref[],int n);

int main(){ 
    printf("Enter the size of the reference String :: ");
    int n; scanf("%d",&n);

    int ref[n];
    printf("Enter the reference string :: ");
    for(int i = 0; i<n; i++){
        scanf("%d",&ref[i]);
    }

    printf("Enter the frame size :: ");
    int frameSize; scanf("%d",&frameSize);

    int flag = 1; 
    while(flag){
        printf("Menu :: 1) FIFO\t2) LRU\t3) Optimal  4) Exit\nChoice :: ");
        int ch; scanf("%d",&ch);
        printf("\n");
        switch (ch)
        {
            case 1:
                fifo(frameSize,ref,n);
                break;
            case 2: 
                LRU(frameSize,ref,n);
                break;
            case 3: 
                optimal(frameSize,ref,n);
                break;
            case 4: 
                flag = 0;
                printf("\nExiting ...\n");
                break;
            default:
                printf("Invalid Input !!!\n\n");
            break;
        }
    }
}

void fifo(int frameSize,int ref[],int n){

    int frame[frameSize][n];

    // Initializing the frame to 0    
    for(int i = 0; i<frameSize; i++){
        for(int j = 0; j<n; j++){
            frame[i][j] = 0;
        }
    }
    // Creating a flag array and initializing to 0
    // 0 = MISS, 1 = HIT
    int hitFlag[n];
    for(int i = 0; i<n; i++){
        hitFlag[i] = 0;
    }

    // Logic for FIFO
    int j = 0;
    for(int i = 0; i<n; i++){
        int page = ref[i];
        j = j%frameSize;
        // Checking for PAGE FAULT
        for(int k = 0; k<frameSize; k++){
            if(i>0) frame[k][i] = frame[k][i-1];
            if(page == frame[k][i]){
                hitFlag[i] = 1; 
                break;
            }
        }

        // if hit else miss
        if( hitFlag[i] == 0 ){
            frame[j][i] = page;
            j++;
        }
        else{
            for (int k = 0; k<frameSize; k++){
                frame[k][i] = frame[k][i-1];
            }
        }
    }

    table(frameSize,n,hitFlag,frame);
}

void LRU(int frameSize,int ref[],int n){

    int frame[frameSize][n];
    // Initializing the frame to 0    
    for(int i = 0; i<frameSize; i++){
        for(int j = 0; j<n; j++){
            frame[i][j] = 0;
        }
    }
    // Creating a flag array and initializing to 0
    // 0 = MISS, 1 = HIT
    int hitFlag[n];
    for(int i = 0; i<n; i++){
        hitFlag[i] = 0;
    }

    int cnt = 0; 
    for(int i = 0; i<n; i++){
        int page = ref[i];
        // Checking for PAGE FAULT
        for(int k = 0; k<frameSize; k++){
            if(i>0) frame[k][i] = frame[k][i-1];
            if(page == frame[k][i]){
                hitFlag[i] = 1; 
                break;
            }
        }

        if(hitFlag[i] == 0){
            // Miss Case
            if(cnt < frameSize){
                frame[cnt][i] = page;
                cnt++;
            }
            else{
                int f[frameSize];
                for(int i = 0; i<frameSize; i++) f[i] = 0; 
   
                /*storing the indexes of the frame elements to find the farthest element*/
                for(int k = 0; k<frameSize; k++){
                    int frameElement = frame[k][i];
                    for(int j = i-1; j>=0; j--){
                        if(ref[j] == frameElement){
                            f[k] = j; 
                            break;
                        }
                    }
                }

                //Finding the farthest frame 
                int miniIndex = 1e9;
                int fReplace = -1;
                for(int k = 0; k<frameSize; k++){
                    if(f[k] < miniIndex){
                        miniIndex = f[k];
                        fReplace = k; 
                    }
                }

                // frame replaced
                // printf("%d-F\n",fReplace);
                frame[fReplace][i] = page;
            }
        }
        else{
            // Hit Case
            for (int k = 0; k<frameSize; k++){
                frame[k][i] = frame[k][i-1];
            }
        }
    }
    // Print the table
    table(frameSize,n,hitFlag,frame);
}

void optimal(int frameSize,int ref[],int n){
    int frame[frameSize][n];
    // Initializing the frame to 0    
    for(int i = 0; i<frameSize; i++){
        for(int j = 0; j<n; j++){
            frame[i][j] = 0;
        }
    }
    // Creating a flag array and initializing to 0
    // 0 = MISS, 1 = HIT
    int hitFlag[n];
    for(int i = 0; i<n; i++){
        hitFlag[i] = 0;
    }

    int cnt = 0; 
    for(int i = 0; i<n; i++){
        int page = ref[i];
        // Checking for PAGE FAULT
        for(int k = 0; k<frameSize; k++){
            if(i>0) frame[k][i] = frame[k][i-1];
            if(page == frame[k][i]){
                hitFlag[i] = 1; 
                break;
            }
        }

        if(hitFlag[i] == 0){
            // Miss Case
            if(cnt < frameSize){
                frame[cnt][i] = page;
                cnt++;
            }
            else{
                int f[frameSize];
                for(int i = 0; i<frameSize; i++) f[i] = 0; 
   
                /*storing the indexes of the frame elements to find the farthest element*/
                for(int k = 0; k<frameSize; k++){
                    int frameElement = frame[k][i];
                    for(int j = i+1; j<n; j++){
                        if(ref[j] == frameElement){
                            f[k] = j; 
                            break;
                        }
                    }
                }

                //Finding the farthest frame 
                int maxIndex = -1e9;
                int fReplace = -1;
                for(int k = 0; k<frameSize; k++){
                    if(f[k] > maxIndex){
                        maxIndex = f[k];
                        fReplace = k; 
                    }
                }

                // frame replaced
                // printf("%d-F\n",fReplace);
                frame[fReplace][i] = page;
            }
        }
        else{
            // Hit Case
            for (int k = 0; k<frameSize; k++){
                frame[k][i] = frame[k][i-1];
            }
        }
    }
    // Print the table
    table(frameSize,n,hitFlag,frame);
}

void table(int frameSize,int refSize, int hitFlag[],int frame[][refSize]){

    int hitCnt = 0; 
    int missCnt = 0; 

    for (int i = 0; i < refSize; i++){
        printf("-------");
    }
    printf("\n|");
    for(int i = 0; i<refSize; i++){
        if(hitFlag[i]){
            printf(" HIT  |");
            hitCnt++;
        }
        else{
            printf(" MISS |");
            missCnt++;
        } 
    }
    printf("\n");
    for (int i = 0; i < refSize; i++){
        printf("-------");
    }
    printf("\n");

    for(int j = 0; j<frameSize; j++){
        printf("|");
        for(int i = 0; i<refSize; i++){
            printf("   %d  |",frame[j][i]);
        }
        printf("\n");
    }

    for (int i = 0; i < refSize; i++){
        printf("-------");
    }
    printf("\n\n");
    printf("Hit  Percent :: %0.2f\n", (float) hitCnt/refSize * 100);
    printf("Miss Percent :: %0.2f\n\n", (float) missCnt/refSize * 100);
}



// Enter the size of the reference String :: 12 
// Enter the reference string :: 1 2 4 2 4 5 3 2 1 3 4 5
// Enter the frame size :: 3 
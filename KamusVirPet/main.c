#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "alien.c"
//#include "petshop.c"  //ga kepake
#include "trader.c"
#include "work.c"
#include "ufo.c"
#define totalHuruf (26) //total huruf = 26
#define charIndex(c) ((int)c - (int)'a') //mengubah char menjadi index
 
int exp = 0;
int hunger = 10;
int friendship = 0;
int food = 10;
int money = 0;
int toy = 2;
 
struct data
{
    struct data *children[totalHuruf];
    bool isLeaf;//menentukan daun atau tidak
};
 
typedef struct data* node;
 
 
node buat(void)
{
    node nodebaru = (node)malloc(sizeof(struct data));
 
    if (nodebaru!=NULL)
    {
        nodebaru->isLeaf = false; 
        int i;
        for (i = 0; i < totalHuruf; i++){
            nodebaru->children[i] = NULL;
        }
            
    }else
    {
        printf("\n\n[ERROR]\n");
    }
    return nodebaru;
}
 
// tambahkan kata ke ingatan kamus
void tambah(node root, const char *key)
{
    node temp = root;
 
    int i;
    for (i = 0; i < strlen(key); i++) //selama jumlah karakter yang di komputasi belum mencapai jumlah karakter yang diinput, maka program akan terus melanjutkan komputasi
    {
        
        int index = charIndex(key[i]); // untuk mendapatkan index dari character.. cth: a=0 , b=1
 
        //cek apakah sudah ada data atau belum. Jika masih kosongan ya diisi wkwk
        if (temp->children[index]==NULL){
            temp->children[index] = buat();
        }
            
 
        //lanjut ke node selanjutnya
        temp = temp->children[index];
    }
 
    //mengindikasikan huruf terakhir (ujung kata)
    temp->isLeaf = true;
}
 
bool isEmpty(node root) //apakah data isinya kosong atau tidak
{
    for (int i = 0; i < totalHuruf; i++)
        if (root->children[i])
            return false;
    return true;
}
 
//untuk mencari data
bool cari( node root, const char *key)
{
    node temp = root;
 
    int i;
    for (i = 0; i < strlen(key); i++) // //selama jumlah karakter yang di komputasi belum mencapai jumlah karakter yang diinput, maka program akan terus melanjutkan komputasi
    {
        int index = charIndex(key[i]); // dijadiin index
 
        if (temp->children[index] == NULL){
            return false;
        }
 
        temp = temp->children[index];
    }
 
    return (temp != NULL && temp->isLeaf);
}
 
 
// Mencari prefix
node traverse(node root, const char *key)
{
    node temp = root;
 
    int i;
    for (i = 0; i < strlen(key); i++) //selama jumlah karakter yang di komputasi belum mencapai jumlah karakter yang diinput, maka program akan terus melanjutkan komputasi
    {
        int index = charIndex(key[i]); // dijadiin index
        if (temp->children[index] == NULL)
        {
            printf("\nNo Words present with the given Prefix: %s \n",key);
            return NULL;
        }
        temp = temp->children[index];
    }
    return temp;
}
 
//babi = 1018
//ba   = 10
 
// untuk validasi character, character yang berlaku hanyalah huruf
char* validation(char* input){
 
    int i;
    for(i=0;i<strlen(input);i++){
        if(!isalpha(input[i])){
            
            return NULL;
        }
    }
    return strlwr(input);
}
 
// menampilkan semua data ingatan kamus.
void printTrieContents(node root, char *buffer, int buffIndex)
{
    bool flag=true;
    int i;
   
    for(i = 0; i < totalHuruf; i++)
    {
        if(root->children[i] != NULL)
        {
            buffer[buffIndex] = i + 'a';
            printTrieContents(root->children[i], buffer, buffIndex + 1);
        }
        if(root->isLeaf && flag)
        {
                buffer[buffIndex] = '\0';
                if(strlen(buffer) > 0)
                {
                    //printf("---> %s \n", buffer);
                    kamusRetell(buffer);
                    printf("---> %s \n", buffer);
                    flag=false;
                }
        }
    }
}
 
void journal(node root, char *buffer, int buffIndex)
{
    bool flag=true;
    int i;
   
    for(i = 0; i < totalHuruf; i++)
    {
        if(root->children[i] != NULL)
        {
                buffer[buffIndex] = i + 'a';
                journal(root->children[i], buffer, buffIndex + 1);
        }
        if(root->isLeaf && flag)
        {
                buffer[buffIndex] = '\0';
                if(strlen(buffer) > 0)
                {
                    //printf("---> %s \n", buffer);
                    printf("---> %s \n", buffer);
                    flag=false;
                }
        }
    }
}
 
node* hapus(node root, const char *key, int depth)
{
    node temp = root;
    
    // If tree is empty
    if (!temp)
        return NULL;
 
    // If last character of key is being processed
    if (depth == strlen(key)) {
 
        // This node is no more end of word after
        // removal of given key
        if (temp->isLeaf)
            temp->isLeaf = false;
 
        // If given is not prefix of any other word
        if (isEmpty(temp)) {
            free(temp);
            temp = NULL;
        }
 
        return temp;
    }
 
    // If not last character, recur for the child
    // obtained using ASCII value
    int index = key[depth] - 'a';
    temp->children[index] = hapus(temp->children[index], key, depth + 1);
 
    // If root does not have any child (its only child got
    // deleted), and it is not end of another word.
    /*if (isEmpty(temp) && temp->isLeaf == false) {
        free(temp);
        
    }*/
 
    //return root;
}
 
 
 
int main()
{
    char buffer[20];
    
 
    node root = buat();
    int buy=0;
 
    printf("Kamus the Alien Virtual Pet\n");
 
    int option ;
    char wordToDictionary[20];
    char wordTocari[20];
    char prefix[20];
    char yesOrNo[10];
    char wordTohapus[20];
    //infinite loop
    while(hunger>=1)
    {
        if (hunger<=3)
        {
            system("cls");
        
            printf("  000\\        /000\n");
            printf("      \\      /\n");
            printf(" 0000___0000___0000__\n");
            printf("|       666         |\n");
            printf("|    ~        ~     |\n");
            printf("|                   |      <----Kamus...  :(\n");
            printf("|     _______       |      it seems like Kamus feel hungry\n");
            printf("|                   |\n");
            printf("| __________________|\n");
        }else if (hunger>3)
        {   
            system("cls");
            printf("    OOO        OOO\n");
            printf("     \\        /\n");
            printf("      \\      /\n");
            printf(" 0000___0000___0000__\n");
            printf("|       666         |\n");
            printf("|    O        O     |\n");
            printf("|                   |      <----Kamus!\n");
            printf("|     _______       |\n");
            printf("|                   |\n");
            printf("| __________________|\n");
        }
        
        
        printf("\n1) Teach\n");
        printf("2) Tell kamus to re tell all what he learned.\n");
        printf("3) Test kamus knowledge.\n");
        printf("4) Test kamus with pre-fix.\n");
        printf("5) Check kamus status.\n");
        printf("6) Feed Kamus\n");
        printf("7) Pet Kamus\n");
        printf("8) Pet Shop\n");
        printf("9) Go to work\n");
        printf("10) Open learning journal.\n");
        printf("11) Brainwash\n");
        printf("12) Goodbye to Kamus.\n");
        printf("Select your option : ");
        scanf("%d",&option);
 
        switch(option)
        {
        case 1:printf("\nEnter the word to teach Kamus : ");
               scanf("%s", wordToDictionary);
                if(validation(wordToDictionary)!=NULL){
                   tambah(root, strlwr(wordToDictionary));
                   exp++;
                   hunger--;
                   friendship++;
                   kamusLearning();
                }else{
                    printf("\nInvalid!\n");
                    getch();
                }
                
                
               break;
 
        case 2:printf("\nContents in the Dictionary are:\n");
               printTrieContents(root,buffer,0);
               break;
 
        case 3:printf("\nEnter the word to test him : ");
               scanf("%s",wordTocari);
               if(validation(wordTocari)!=NULL)
                {
                    if(cari(root,wordTocari))
                        kamusTest(wordTocari);
                else
                {
                    kamusFailedTest(wordTocari);
 
                    printf("\nShall we teach this word ? (Yes or No):");
                    scanf("%s",yesOrNo);
                    if(strcmp("yes",yesOrNo)==0||strcmp("YES",yesOrNo)==0||strcmp("Yes",yesOrNo)==0)
                            tambah(root, wordTocari);
                            exp++;
                            hunger--;
                            friendship++;
 
                }
                }else{
                    printf("\ninvalid\n");
                }
                break;
 
        case 4:printf("\nEnter the PREFIX : ");
               scanf("%s",prefix);
               if(validation(prefix)!=NULL)
               {
                    strcpy(buffer,prefix);
                    //printf("\nPrinting all the dictionary words with given PRIFIX : %s \n",prefix);
                    node prefixRoot= traverse(root,prefix);
                    if(prefixRoot!=NULL)
                        {
                            printTrieContents(prefixRoot,buffer,strlen(prefix));
                        }
                }
                break;
 
        case 12: if (friendship<=5)
            {
                printufo();
                getch();
            }else if (friendship>=6)
            {
                printufoPeace();
                getch();
            }
        
        
            exit(0);
        
        case 5:kamusProfile(exp,hunger,friendship,food,money,toy);
            break;
        
        case 6:
            if(food==0){
                printf("Not enough food, buy it in pet shop\n");
                getch();
            }else{
                kamusEating();
                food--;
                hunger++;
            }
            
            break;
        
        case 7:
            if (toy==0)
            {
                printf("Not enough toy, buy it in petshop\n");
            }else{
                kamusPlay();
                friendship++;
                hunger--;
                toy--;
            }
            break;
        
        case 8:
 
            
            while (buy!=3)
            {
                system("cls");
                printtrader();
                printf("\nYour coin : [%d coin]\n",money);
                printf("1. Food  [2 coin]\n");
                printf("2. Toy   [6 coin]\n");
                printf("3. Thankyou\n");
                printf("Select your choice :");
                scanf("%d",&buy);
                if (buy==1)
                {
                    if (money>=2)
                    {
                        food++;
                        money=money-2;
                    }else if (money<2)
                    {
                        printf("\nNot enough coin\n");
                        getch();
                        
                    }
                    
                }else if (buy==2)
                {   
                    if (money>=6)
                    {
                        toy++;
                        money=money-6;
                    }else if (money<2)
                    {
                        printf("\nNot enough coin\n");
                        getch();
                        
                    }
                
                }
            }
            buy=0;
            break;
        
        case 9: system("cls"); 
            printwork();
            getch();
            money=money+2;
            break;
        
        case 10: 
            printf("===========================================\n");
            printf("            Kamus Learning Journal         \n");
            printf("===========================================\n");
            journal(root,buffer,0);
            printf("Press enter to close journal\n");
            getch();
            break;
 
        case 11:
            printf("===========================================\n");
            printf("                 Brainwash lab        \n");
            printf("===========================================\n");
            printf("Select what word to forget : \n");
            journal(root,buffer,0);
            scanf("%s", wordTohapus);
            if(validation(wordTohapus)!=NULL){
                hapus(root,wordTohapus,0);
                hunger--;
                friendship--;
            }else{
                printf("\nINVALID\n");
                getch();
            }
            
            break;
 
 
        default:printf("\n\nInvalid Option.\n\n");
        }
    }
 
    kamusDeath();
    getch();
    return 0;
}
 
 

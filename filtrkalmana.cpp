#include<iostream>

class filtrkalmana {
    private:
        float estym;
        float estym_pop;
        float BLAD;
        float ostatni_pomiar;
        
        float SPR;
        float SPO;
        
        int ilosc;

        public:
        filtrkalmana() : ilosc(0),estym(0),SPR(0),SPO(0),BLAD(1) {}
        float dodaj(float wart){
            if(ilosc==0){
                estym = wart;
            }
            else{
                float x=ostatni_pomiar-wart;
                if(x<0) x=-x;
                SPO=(SPO*ilosc+x)/(ilosc+1);

                float estym_przew=estym;
                float BLAD_przew=BLAD+SPR;
                
                float wzmocnienie=BLAD_przew/(BLAD_przew+SPR);

                estym=estym_przew+wzmocnienie*(wart-estym_przew);
                BLAD=(1-wzmocnienie)*BLAD_przew;

                float z=estym-estym_pop;
                SPR=(SPR*ilosc+z)/(ilosc+1);
                
            }
            estym_pop=estym;
            ostatni_pomiar = wart;
            ilosc++;
            return estym;
        }
};

int main(){
    float f,wyniki[3000];
    int x=0;
    filtrkalmana *kalman=new filtrkalmana();
    while(scanf("%.4f",f))
    {
        wyniki[x]=kalman->dodaj(f);
        x++;
    }
    for(int j=0;j<10;j++){
        filtrkalmana *kal=new filtrkalmana();
        for(int i=0;i<x;i++){
            wyniki[i]=kal->dodaj(wyniki[i]);
        }
    }
    for(int i=0;i<x;i++){
        printf("%.4f\n",wyniki[i]);
    }
}
#include <iostream>
#include <time.h>
using namespace std;



int main()
{
    setlocale(LC_ALL, ".1251");
    char s1[] = "mamam  myla ramu 5 da diid ttty 11", s2[255] = "";     
    int n = strlen(s1);
    
    __asm {  
        cld;// просмотр вперёд
        lea esi, s2
        mov edx, esi;// сохраняем начало строки s2 в edx
        lea edi, s1;// esi на начало строки s1

        mov ecx, n    
        inc ecx;// для корректного определения последнего слова
        mov al, ' '
    
    findWord:  
        repz scasb;// пропуск пробелов    
        mov esi, edi;// esi-1 - начало слова
        repnz scasb;// пропуск не пробелов     
        push ecx

        mov ecx, edi;// edi-2 - конец слова
        sub ecx, esi;// ecx - длина слова    
        dec esi;// esi - начало слова  
    
    ;// определение палиндром ли текущее слово
        push esi
        push edi
        push eax
        push ecx        
         
        mov ebx, 1;// 1 - палиндром, 0 - нет                 
    
        shr ecx, 1;// делим длину слова на 2
        jecxz yes;// если ecx == 0, слово из 1 буквы всегда палиндром

        sub edi, 2;// edi - конец слова
       
    l1:
         mov al, es : [esi]
         cmp al, es : [edi]
         jnz no         
         inc esi        
         dec edi
         loop l1
         jmp yes

    no:
        mov ebx, 0

    yes:        
        pop ecx
        pop eax
        pop edi
        pop esi
 
    cmp ebx, 1
    jnz skipWord;// пропускаем, если не палиндром
    
    ;// копируем слово
        push esi
        push edi
        
        mov edi, edx
        repe movsb;// копируем ecx символов из esi в edi
        mov byte ptr [edi], ' '
        inc edi
        mov edx, edi;// сохраняем конец строки s2
        
        pop edi
        pop esi
   
    skipWord:
        pop ecx  
        test ecx,ecx
        jnz findWord;// если не конец строки
    }

    cout << "В строке: " << s1 << endl;
    if (strlen(s2) == 0) {
        cout << "cлова-палиндромы не найдены" << endl;
    }
    else {
        cout << "найдены cлова-палиндромы: " << s2 << endl;
    } 
 }
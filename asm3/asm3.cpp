#include <iostream>
#include <time.h>
using namespace std;



int main()
{
    setlocale(LC_ALL, ".1251");
    char s1[] = "mamam  myla ramu   da diid t ", s2[255] = "";      
    
    __asm {  
        cld;// просмотр вперёд
        lea edi, s2
        mov edx, edi;// сохраняем начало строки s2 в edx
        lea esi, s1;// esi на начало строки s1

    ;// пропуск пробелов
    skipSpace:
        lodsb;// загрузить символ из es:[esi] в al
        cmp al, ' '
        jz skipSpace
        test al, al
        jz endAll;// конец строки
            
    ;// выделение слова
        mov edi, esi;// edi-1 первая буква слова        
    letter:            
        cmp al, 0
        jz stop
        cmp al, ' '
        jz stop         
        lodsb
        jmp letter
    
    stop:
        mov ecx, esi;// esi-2 последняя буква слова
        sub ecx, edi;// ecx - длина слова                
        dec edi; // edi - начало слова

    ;// определение палиндром ли текущее слово
        push esi
        push edi
        push eax
        push ecx        
         
        mov ebx, 1;// 1 - палиндром, 0 - нет         
        sub esi, 2;// esi - конец слова
    
        shr ecx, 1;// делим длину слова на 2
        jecxz yes;// если ecx == 0, слово из 1 буквы всегда палиндром

    l1:
         mov al, es : [edi]
         cmp al, es : [esi]
         jnz no         
         inc edi        
         dec esi
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
        
        mov esi, edi
        mov edi, edx
        repe movsb;// копируем ecx символов из esi в edi
        mov byte ptr [edi], ' '
        inc edi
        mov edx, edi;// сохраняем конец строки s2
        
        pop edi
        pop esi
   
    skipWord:
        test al,al
        jnz skipSpace;

     endAll:             
    }

    cout << "В строке: " << s1 << endl;
    if (strlen(s2) == 0) {
        cout << "cлова-палиндромы не найдены" << endl;
    }
    else {
        cout << "найдены cлова-палиндромы: " << s2 << endl;
    } 
 }

#include "functions.h"
int main() {
    //while(){
    printf("Выберите пункт меню\n\n");
    printf("1\t Вывести список логических дисков\n");
    printf("2\t Cоздать файл\n");
    printf("3\t Создать дерикторию\n");
    printf("4\t Удалить дерикторию\n");
    printf("5\t Получить сведения  о файле\n");
    printf("6\t Изменить права доступа к файлу\n");
    printf("Введие номер выбранного пункта: ");
    char userChose;
    scanf("%c",&userChose);
    //system("df -h");
    switch(userChose){
        case '1':
            showDiscs();
            break;
        case '2':
            createFile();
            break;
        case '3':
            makeFolder();
            break;
        case '4':
            removeFolder();
            break;
        case '5':
            getFileAttribute();
            break;
        case '6':
            changeAttributeAcces();
        case '7':
            setFileTime();
            break;
        case '0':
            exit(1);
        default:
            break;
        }
  //  }
    return  0;
}

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Ham xoa ki tu thua
void XoaKyTuThua(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF); //EOF: Ki hieu ket thuc tap tin
}

//Tao kieu du lieu SinhVien
typedef struct{
    char hoten[50];
    char mssv[20];
    int namsinh;
    float gpa;
} SinhVien;

//Tao cau truc cho Node
typedef struct Node{
    SinhVien data;
    struct Node *next; 
} Node;

//Tao Node
Node *taoNode(SinhVien sv){
    Node *p = (Node*)malloc(sizeof(Node)); //Cap phat bo nho cho KDL Node
    p->data = sv; //Thuoc tinh sv dc gan vao data trong KDL Node
    p->next = NULL;
    return p;
}

//Ham them Node vao cuoi danh sach
void addNode(Node **head, SinhVien sv){
    Node *newNode = taoNode (sv);
    //head -> Node dau tien neu ban dau la danh sach rong
    if (*head == NULL){
        *head = newNode; 
        return;
    }
    //neu khong la danh sach rong, Node truoc -> Node sau
    Node *temp = *head;
    while (temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newNode;
}

//Ham nhap thong tin 1 sinh vien
void nhapSV(SinhVien *sv){
    printf("Ho va ten: ");
    fgets(sv->hoten, sizeof(sv->hoten), stdin);
    sv->hoten[strcspn(sv->hoten, "\n")] = '\0';

    printf("MSSV: ");
    fgets(sv->mssv, sizeof(sv->mssv), stdin);
    sv->mssv[strcspn(sv->mssv, "\n")] = '\0';

    printf("Nam sinh: ");
    scanf("%d", &sv->namsinh);

    printf("GPA: ");
    scanf("%f", &sv->gpa);

    XoaKyTuThua();
}

//In danh sach
void InDanhSach(Node *head){
    printf("DANH SACH SINH VIEN: \n");
    Node *temp = head;
    while (temp != NULL){
        printf("%-20s %-10s %-10d %.2f\n", 
                temp->data.hoten,
                temp->data.mssv,
                temp->data.namsinh,
                temp->data.gpa);
        temp = temp->next;
    }
}

//Ham tinh chieu dai danh sach
int DoDai(Node *head){
    int count = 0;
    Node *p = head;
    while (p != NULL){
        count++;
        p = p->next;
    }
    return count;
}

//Ham dem so sinh vien co GPA > 3.2
int demGPA(Node *head){
    int dem = 0;
    Node *temp = head;
    while (temp != NULL){
        if (temp->data.gpa > 3.2){
            dem++;
        }
        temp = temp->next;
    }
    return dem;
}

//Ham sap xep danh sach sinh vien theo GPA = Bubble Sort
void BubbleSort(Node *head){
    if (head == NULL) return;
    int swap;
    Node *start;
    Node *last = NULL;
    do{
        swap = 0;
        start = head;
        while(start->next != last){
            if(start->data.gpa > start->next->data.gpa){
                SinhVien temp = start->data;
                start->data = start->next->data;
                start->next->data = temp;
                swap = 1;
            }
            start = start->next;
        }
        last = start;
    } while (swap);
}

//Chen sinh vien moi theo thu tu GPA
void InsertGPA(Node **head, SinhVien sv){
    Node *newNode = taoNode(sv);
    //Neu danh sach rong hoac GPA min
    if(*head == NULL || sv.gpa < (*head)->data.gpa){
        newNode->next = *head;
        *head = newNode;
        return;
    }
    //Khong phai truong hop tren
    Node *temp = *head;
    while (temp->next != NULL && temp->next->data.gpa < sv.gpa){
        temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

//Ham main
int main(){
    Node *head = NULL; //tao danh sach rong
    int n;
    printf("Nhap so sinh vien: "); 
    scanf("%d", &n);
    XoaKyTuThua();

    //Nhap thong tin sinh vien
    for (int i = 0; i < n; i++){
        printf("\nNhap sinh vien thu %d: \n", i+1);
        SinhVien sv;
        nhapSV(&sv);
        addNode(&head, sv);
    }

    printf("Danh sach co: &d sinh vien", n);
    InDanhSach(head);
    printf("\nChieu dai cua danh sach la: %d", DoDai(head));
    printf("\nSo luong sinh vien co GPA > 3.2 la: %d", demGPA(head));
    BubbleSort(head);
    printf("\nDANH SACH SAU KHI SAP XEP GPA TANG DAN: ");
    InDanhSach(head);

    //Them vao 1 sinh vien GPA = 2.4
    SinhVien moi = {"Sinh vien A", "202414229", 2006, 2.4};
    InsertGPA(&head, moi);
    printf("\n\nDANH SACH SAU KHI CHEN SINH VIEN GPA = 2.4: \n");
    InDanhSach(head);

    return 0;
}
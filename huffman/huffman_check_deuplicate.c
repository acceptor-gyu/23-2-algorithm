#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENT 200

static int sequence = 1;

typedef struct {
    char key;
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair *data;
    int size;
    int capacity;
} Map;

void initializeMap(Map *map) {
    map->data = (KeyValuePair *)malloc(sizeof(KeyValuePair) * MAX_ELEMENT);
    map->size = 0;
    map->capacity = MAX_ELEMENT;
}

void addToMap(Map *map, char key, int value) {

    // 맵의 사이즈를 기존 사이즈의 2배로 늘림.
    if (map->size >= map->capacity) {
        map->capacity *= 2;
        map->data = (KeyValuePair *)realloc(map->data, sizeof(KeyValuePair) * map->capacity);
    }

    // 중복 처리
    for (int i = 0; i < map->size; ++i) {

        if (map->data[i].key == key) {
            map->data[i].value = 0;
            return;
        }
    }

    map->data[map->size].key = key;
    map->data[map->size].value = value;
    map->size++;
}

int getValue(Map *map, char key) {

    for (int i = 0; i < map->size; i++) {
        if (map->data[i].key == key) {
            return map->data[i].value;
        }
    }

    return 0;
}

void extractMapToArray(Map *map, char keys[], int values[], int *numValidPairs) {

    *numValidPairs = 0;  // 유효한 쌍의 수를 추적하는 변수 초기화

    for (int i = 0; i < map->size; i++) {
        if (map->data[i].value != 0) {
            keys[*numValidPairs] = map->data[i].key;
            values[*numValidPairs] = map->data[i].value;
            (*numValidPairs)++;
        }
    }
}

int compare(const void *a, const void *b) {
    return ((KeyValuePair *)a)->value - ((KeyValuePair *)b)->value;
}

typedef struct TreeNode {
    int weight;
    char ch;
    char* uuid;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct {
    TreeNode* ptree;
    char ch;
    int key;
    char* uuid;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

HeapType* create() {

    return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) {

    h->heap_size = 0;
}

void insert_min_heap(HeapType* h, element item) {

    int i;
    i = ++(h->heap_size);

    // 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
    while ((i != 1) && (item.key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;  // 새로운 노드를 삽입
}

element delete_min_heap(HeapType* h) {

    int parent, child;
    element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;

    while (child <= h->heap_size) {

        // 현재 노드의 자식 노드 중 더 작은 자식 노드를 찾는다.
        if ((child <= h->heap_size) &&
            (h->heap[child].key) > h->heap[child + 1].key) {
            child++;
        }

        if (temp.key < h->heap[child].key) {
            break;
        }

        // 한 단계 아래로 이동
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }

    h->heap[parent] = temp;

    return item;
}

// 이진 트리 생성 함수
TreeNode* make_tree(TreeNode* left, TreeNode* right) {

    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    return node;
}

// 이진 트리 제거 함수
void destroy_tree(TreeNode* root) {

    if (root == NULL) {
        return;
    }

    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

// 단말 노드인지 아닌지 검사하는 함수
int is_leaf(TreeNode* root) {

    return !(root->left) && !(root->right);
}

void print_array(int codes[], int n) {

    for (int i = 0; i < n; i++) {
        printf("%d", codes[i]);
    }

    printf("\n");
}

void print_codes(TreeNode* root, int codes[], int top) {

    // 1을 저장하고 순환 호출한다.
    if (root->left) {
        codes[top] = 1;
        print_codes(root->left, codes, top + 1);
    }

    // 0을 저장하고 순환 호출한다.
    if (root->right) {
        codes[top] = 0;
        print_codes(root->right, codes, top + 1);
    }

    // 단말 노드이면 코드를 출력한다.
    if (is_leaf(root)) {
        printf("%c: ", root->ch);
        print_array(codes, top);
    }
}

void preorder_traversal(TreeNode* root) {

    if (root == NULL) {
        return;
    }

    if (root->ch != NULL) {
        printf("%s ", root->uuid);
        printf("문자: %c\n", root->ch);
    }

    preorder_traversal(root->left); // 왼쪽 서브트리 순회
    preorder_traversal(root->right); // 오른쪽 서브트리 순회
}

// 허프만 코드 생성 함수
void huffman_tree(int freq[], char ch_list[], int n) {

    int i;
    TreeNode *node, *x;
    HeapType* heap;
    element e, e1, e2;
    int codes[100];
    int top = 0;

    heap = create();
    init(heap);

//    asprintf(&(map->data[map->size].uuid), "H-%d", sequence);

    for (i = 0; i < n; i++) {
        node = make_tree(NULL, NULL);
        e.ch = node->ch = ch_list[i];
        e.key = node->weight = freq[i];
        asprintf(&node->uuid, "H-%d", sequence);
        asprintf(&e.uuid, "H-%d", sequence);
        sequence++;
//        e.uuid = node->uuid =
        e.ptree = node;
        insert_min_heap(heap, e);
    }

    printf("\n");

    for (i = 1; i < n; i++) {
        // 최소값을 가지는 두 개의 노드를 삭제
        e1 = delete_min_heap(heap);
        e2 = delete_min_heap(heap);

        // 두 개의 노드를 합친다.
        x = make_tree(e1.ptree, e2.ptree);
        e.key = x->weight = e1.key + e2.key;
        e.ptree = x;
        printf("%d+%d->%d \n", e1.key, e2.key, e.key);
        insert_min_heap(heap, e);
    }

    e = delete_min_heap(heap); // 최종 트리

    element peekedElement = heap->heap[1];
    preorder_traversal((TreeNode *) peekedElement.ptree);

    print_codes(e.ptree, codes, top);
    destroy_tree(e.ptree);
    free(heap);
}

int main(void) {


    Map map;
    initializeMap(&map);

    FILE *file = fopen("../huffman/huff_data/huff_B.txt", "r");

    if (file == NULL) {
        perror("파일 열기 실패");
        return 1;
    }

    int expectedCount;
    printf("문자 개수? ");
    fscanf(file, "%d", &expectedCount);
    printf("%d\n", expectedCount);

    char character;
    int frequency;

    for (int i = 0; i < expectedCount; i++) { // 파일에서 문자 읽기 (공백 문자 무시)

        int c;
        while ((c = fgetc(file)) != EOF && c != '\n');

        printf("문자? ");
        fscanf(file, "%c", &character);
        printf("%c\n", character);

        printf("빈도수? ");
        fscanf(file, "%d", &frequency);
        printf("%d\n", frequency);

        addToMap(&map, character, frequency);

        if (feof(file)) {
            break;
        }
    }

    fclose(file);

    char keys[MAX_ELEMENT];
    int values[MAX_ELEMENT];
    int countOfValidatedPairs;

    extractMapToArray(&map, keys, values, &countOfValidatedPairs);

    KeyValuePair  *pairs = (KeyValuePair *)malloc(sizeof(KeyValuePair) * countOfValidatedPairs);

    qsort(pairs, countOfValidatedPairs, sizeof(KeyValuePair), compare);

    huffman_tree(values, keys, countOfValidatedPairs);

    // 맵 메모리 해제
    free(map.data);
    free(pairs);

    return 0;
}
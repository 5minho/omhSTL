//
// Created by 오민호 on 2017. 3. 24..
//

#ifndef MSTL_LIST_H
#define MSTL_LIST_H

#include <cstddef>

namespace omh {
    template <typename T>
    class list {
    private:
        //이중 연결 리스트의 노드 정의
        struct node {
            T data;
            node* prev;
            node* next;
            node(T data = 0):data(data) {
                prev = next = 0;
            }
        };

        node* head; //노드의 첫번째 위치
        node* tail; //노드의 마지막 위치
        size_t bsize; //노드 개수

    public:
        //반복자 정의
        class iterator {
            node* cur; // 현재 가르키고 있는 위치
        public:
            iterator(node* cur): cur(cur) {}

            T& operator*() {
                return cur->data; // 포인터 연산자 재정의
            };

            operator node*() {
                return cur; // list내에서 node*와 반복자간의 묵시적 형변환 가능하게 함
            }

            bool operator==(const iterator& ref) {
                return cur == ref.cur;
            }

            bool operator!=(const iterator& ref) {
                return cur != ref.cur;
            }

            iterator& operator++() { //전위 증가 연산자
                cur = cur -> next;
                return *this;
            }

            const iterator operator++(int) { //후위 증가 연산자 정의
                iterator ret(*this);
                cur = cur->next;
                return ret;
            }

        };

        //더미노드를 이용해서 생성자 정의
        //더미노드를 사용하면 노드 추가 삭제 구현이 간단해 진다.
        list() {
            head = new node;
            tail = new node;
            head->next = tail;
            head->prev = nullptr;
            tail->next = nullptr;
            tail->prev = head;
            bsize = 0;
        }
        ~list() {
            while (head != tail) { // head와 tail이 같아 지면 종료
                head = head->next; // head를 앞으로 이동시키며
                delete head->prev; // 이전 head를 소멸시킨다
            }
            delete head;//마지막 남은 (head = tail) 소멸
        }
        void insert(iterator at, T t) {
            node* pos = at;//반복자의 묵시적 형변환 연산자 호출
            node* curNode = new node(t);
            curNode->next = pos;
            curNode->prev = pos->prev;
            pos->prev->next = curNode;
            pos->prev = curNode;
            bsize++;
        }

        void push_back(T t) { //end()가 가리키는 요소 앞에 t삽입
            insert(end(), t);
        }

        void erase(iterator at, int flag = 0) { // resize 함수 때문에 flag 변수 추가
            node* pos = at;
            if(flag == 1) pos = pos->prev; // flag가 1이면 at 가리키는 요소의 전 요소를 삭제한다.
            pos->next->prev = pos->prev;
            pos->prev->next = pos->next;
            delete pos;
            bsize--;
        }
        iterator begin() { // head는 더미 노드이기 때문에 head->next 반환
            return head->next;
        }

        iterator end() { // tail은 더미 노드이기 때문에 그대로 tail반환 (end는 마지막 요소의 다음 요소를 가리킴)
            return tail;
        }

        size_t size() {
            return bsize;
        }

        void resize(size_t nsize) {
            if(bsize < nsize) {
                for(size_t n = bsize ; n < nsize ; ++n)
                    insert(end(),0);
            } else {
                for(size_t n = nsize ; n < bsize ;) {
                    erase(end(),1);
                }
            }
        }
    };
}

#endif //MSTL_LIST_H

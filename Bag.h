#ifndef BAG_H
#define BAG_H

template <class Item> 
class Bag
{
 private:
  Item * v;
  int n;
  int tam;
  void resize(int tam);

 public: 
  Bag();
  ~Bag();
  void add(Item item);
  bool isEmpty();
  int size();
  Item at(int i); 
};

template <class Item>
Bag<Item>::Bag(): n(0), tam(1), v(new Item[1]) {};

template <class Item>
Bag<Item>::~Bag() {
  if (v != nullptr)
    delete [] v;
}

template <class Item> 
void Bag<Item>::add (Item item) {
  if (n == tam)
    resize(2 * tam);
  v[n] = item;
  n++;
}

template <class Item> 
bool Bag<Item>::isEmpty () {
  return (n == 0);
}

template <class Item>
int Bag<Item>::size() {
  return (n);
}

template <class Item>
Item Bag<Item>::at(int i) {
  if (i >= 0 && i < n)
    return (v[i]);
}

template <class Item>
void Bag<Item>::resize(int t) {
  Item * novoV = new Item[t];
  for (int i = 0; i < n; i++)
    novoV[i] = v[i];
  delete [] v;
  v = novoV;
  tam = t;
}


#endif

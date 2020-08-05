using System;


namespace dynamicDoublyLinkedList {

	public class DynamicDoublyLinkedList<T>
	{

		public DynamicDoublyLinkedList<T> next;
		public DynamicDoublyLinkedList<T> previous;
		private T val;


		public DynamicDoublyLinkedList(T val) {
			this.next = null;
			this.previous = null;
			this.val = val;
		}

		public void Add(T value) {
			DynamicDoublyLinkedList<T> toAdd = new DynamicDoublyLinkedList<T>(value);
			if (this.next == null) {
				this.next = toAdd;
				toAdd.previous = this;
			} else {
				this.next.previous = toAdd;
				toAdd.next = this.next;
				this.next = toAdd;
				toAdd.previous = this;
			}
		}

		public DynamicDoublyLinkedList<T> Search(T val) {
			if (val.Equals(this.val)) {
				return this;
			} else if (this.next != null) {
				return this.next.Search(val);
			} else {
				return null;
			}
		}

		public void print() {
			Console.WriteLine(this.val);
			if (this.next != null)
				this.next.print();
		}


		private int countElements() {
			if (this.next != null)
				return this.next.countElements() + 1;
			else
				return 1;
		}

		public T[] GetArray() {
			int elementsCount = this.countElements();
			T[] arrayElements = new T[elementsCount];
			DynamicDoublyLinkedList<T> ptr = this;
			for (int i = 0; i < elementsCount; i++) {
				arrayElements[i] = ptr.val;
				ptr = ptr.next;
			}
			return arrayElements;
		}

		public void Remove(T val) {
			DynamicDoublyLinkedList<T> element = this.Search(val);
			if (element == null) {
				//throw exception
			}

			element.previous.next = element.next;
			element.next.previous = element.previous;
		}

	}
}

/**
 * Introduction to Algorithms 2016 Spring
 * Homework #2 Sort (Binary Input)
 * by Yu-wen Pwu (rev1)
 */

import org.msgpack.core.MessagePack;
import org.msgpack.core.MessagePacker;
import org.msgpack.core.MessageUnpacker;
import java.io.FileInputStream;
import java.io.FileOutputStream;

public class Code {

public static void main(String[] args) {
	try {
		Code code = new Code();
		MessageUnpacker unpacker = MessagePack.newDefaultUnpacker(new FileInputStream("input.txt"));
		MessagePacker packer = MessagePack.newDefaultPacker(new FileOutputStream("output.txt"));
		int count = unpacker.unpackInt();
		for (int i = 0; i < count; i++) {
			int length = unpacker.unpackArrayHeader();
			Heap heap = new Heap(length);
			for (int j = 0; j < length; j++)
				heap.data[j] = unpacker.unpackInt();
			code.heapSort(heap);
			packer.packArrayHeader(length);
			for (int j = 0; j < length; j++)
				packer.packInt(heap.data[j]);
		}
		unpacker.close();
		packer.close();
	}
	catch (Exception e) {
		e.printStackTrace();
	}
	System.exit(0);
}

private void heapify(Heap heap, int current) {
	int left = Heap.leftChild(current);
	int right = Heap.rightChild(current);
	int largest = (left <= heap.size && heap.data[left] > heap.data[current]) ? left : current;
	largest = (right <= heap.size && heap.data[right] > heap.data[largest]) ? right : largest;
	if (largest != current) {
		int temp = heap.data[current];
		heap.data[current] = heap.data[largest];
		heap.data[largest] = temp;
		heapify(heap, largest);
	}
}

private void buildHeap(Heap heap) {
	heap.size = heap.data.length;
	for (int i = heap.size/2-1; i >= 0; i--)
		heapify(heap, i);
}

private void heapSort(Heap heap) {
	buildHeap(heap);
	for (int i = heap.size-1; i >= 1; i--) {
		int temp = heap.data[i];
		heap.data[i] = heap.data[0];
		heap.data[0] = temp;
		heap.size--;
		heapify(heap, 0);
	}
}

private int heapExtractMax(Heap heap) throws Exception {
	if (heap.size == 0)
		throw new Exception("Heap Underflow");
	int max = heap.data[0];
	heap.data[0] = heap.data[heap.size-1];
	heap.size--;
	heapify(heap, 0);
	return max;
}

private void heapInsert(Heap heap, int key) throws Exception {
	if (heap.size == heap.data.length)
		throw new Exception("Heap Overflow");
	heap.size++;
	int i = heap.size-1;
	while (i > 0 && heap.data[Heap.parent(i)] < key) {
		heap.data[i] = heap.data[Heap.parent(i)];
		i = Heap.parent(i);
	}
	heap.data[i] = key;
}

}

class Heap {

int[] data;
int size;

Heap(int i) {
	data = new int[i];
	size = 0;
}

static int leftChild(int i) {
	return 2*i+1;
}

static int rightChild(int i) {
	return 2*i+2;
}

static int parent(int i) {
	return (i-1)/2;
}

}

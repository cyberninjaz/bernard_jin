import java.util.function.Function;
import java.util.Arrays;

class Node<T> {
	T data;
	Node<T> nextNode;
	Node(T Data) {
		this.data = Data;
	}
	Node() {
		this.data = null;
	}
	T getData() {
		return data;
	}
	boolean setNextNode(Node<T> nextnode) {
		if(nextnode != null) {
			this.nextNode = nextnode;
			return true;
		}
		else {
			return false;
		}
	}
	public String toString() {
		return data.toString();
	}
}

class LinkedList<T> {
	private Node<T> startNode;
	private int length = 0;
	LinkedList() {

	}
	void append(Node<T> node) {
		if(length == 0) {
			startNode = node;
		}
		else {
			node.nextNode = startNode;
			startNode = node;
		}
		length++;
	}
	void takeOut(Node<T> location) {
		if(location == null) {
			length--;
			startNode = startNode.nextNode;
		}
		else {
			length--;
			location.nextNode = location.nextNode.nextNode;
		}
	}
	Node<T> getStartNode() {
		return startNode;
	}
	public String toString() {
		StringBuilder outString = new StringBuilder();
		Node<T> currNode = startNode;
		while(currNode != null) {
			outString.append(currNode).append(", ");
			currNode = currNode.nextNode;
		}
		return outString.toString();
	}
}

public class Hashtable<T> {
    private int size = 0;
	private LinkedList<T>[] array;
	private Function<T, Integer> hash;
	private static final int GROW_FACTOR = 2;
	private double load_factor;

    public Hashtable() {
        this(x -> x.hashCode());
    }

    public Hashtable(Function<T, Integer> hash) {
		array = (LinkedList<T>[]) new LinkedList[101];
		for(int x = 0; x < array.length; x++) {
			array[x] = new LinkedList<T>();
		}
        this.hash = hash;
    }

    private int hCode(T element) {
        int htemp = hash.apply(element) % array.length;
        if(htemp < 0) {
			return htemp + array.length;
		}
		return htemp;
    }

    public boolean add(T element) {
		int htemp = hCode(element);
		if(load_factor >= .75) {
			var temp = (LinkedList<T>[]) new LinkedList[array.length * GROW_FACTOR];
			for(int x = 0; x < temp.length; x++) {
				temp[x] = new LinkedList<T>();
			}
			for(int x = 0; x < array.length; x++) {
				Node<T> currNode = array[x].getStartNode();
				Node<T> firstNode = currNode;
				while(currNode != null && firstNode.getData() == currNode.getData()) {
					int y = hCode(currNode.getData());
					temp[y].append(currNode);
					currNode = currNode.nextNode;
				}
			}
			array = temp;
		}
		Node<T> currNode = array[htemp].getStartNode();
		while(currNode != null) {
			if(currNode.getData().equals(element)) {
				return false;
			}
			else {
				currNode = currNode.nextNode;
				load_factor = size / array.length;
			}
		}
        size++;
        array[htemp].append(new Node<T>(element));
        return true;
    }

    public boolean remove(T element) {
		int htemp = hCode(element);
		Node<T> lastNode = null;
		Node<T> currNode = array[htemp].getStartNode();
        while(currNode != null) {
			if(currNode.getData().equals(element)) {
				array[htemp].takeOut(lastNode);
				size--;
				return true;
			}
			else {
				lastNode = currNode;
				currNode = currNode.nextNode;
			}
		}
		return false;
    }
    
    public boolean contains(T element) {
        int htemp = hCode(element);
		Node<T> currNode = array[htemp].getStartNode();
        while(currNode != null) {
			if(currNode.getData().equals(element)) {
				return true;
			}
			else {
				currNode = currNode.nextNode;
			}
		}
		return false;
    }

    public int size() {
        return size;
	}
	
	public String toString() {
		StringBuilder outString = new StringBuilder();
		for(int x = 0; x < array.length; x++) {
			if(array[x].getStartNode() != null) {
				outString.append(x).append(". ").append(array[x]).append("\n");
			}
		}
		return outString.toString();
	}
}
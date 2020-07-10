import java.util.Arrays;

@SuppressWarnings("unchecked")  // BE CAREFUL! This stops compiler from complaining about unchecked cast from Object[] to T[]
public class Stack<T> {
	private static final double GROW_FACTOR = 2;  // must be greater than 1
	private static final double SHRINK_LIMIT = 0.25;  // must be less then 1/GROW_FACTOR and non-negative

	private T[] array;
	private int sp = 0;  // stack pointer: next available position
	private int min_capacity;
	
	// constructor
	public Stack(int length) {
		if (length <= 0)
			throw new IllegalArgumentException("minimum stack capacity must be at least 1");
		
		array = (T[]) new Object[length];
		min_capacity = length;
	}

	public Stack() {
		this(10);
	}
	
	public void push(T element) {
		// resize array if nessesary
		if(sp == array.length) {
			T[] temp_array = (T[]) new Object[(int) Math.ceil(array.length * GROW_FACTOR)];
			System.arraycopy(array, 0, temp_array, 0, array.length);  // O(n)
			array = temp_array;
		}

		// push element
		array[sp++] = element;
	}
	
	public T peek() {
		return array[sp - 1];
	}

	public int size() {
		return sp;
	}

	public boolean isEmpty() {		
		return sp == 0;
	}

	public T pop() {
		if (sp == 0)
			throw new IllegalStateException("Can't pop from empty stack");

		// pop top element
		T element = array[--sp];

		// shrink array if it reaches SHRINK_LIMIT
		if(array.length > min_capacity && sp <= array.length * SHRINK_LIMIT) {
			T[] temp_array = (T[]) new Object[(int) Math.ceil(array.length / GROW_FACTOR)];
			System.arraycopy(array, 0, temp_array, 0, sp);  // O(n)
			array = temp_array;
		}

		// return removed element
		return element;
	}

	public String toString() {
		return String.format("array: %s  sp: %s", Arrays.toString(array), sp);
	}
}

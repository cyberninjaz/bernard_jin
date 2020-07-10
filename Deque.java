import java.util.Arrays;

public class Deque<T> {
    private static final double GROW_FACTOR = 2;  // must be greater than 1
	private static final double SHRINK_LIMIT = 0.25;  // must be less then 1/GROW_FACTOR and non-negative
    private int min_capacity;
    private int front_pointer = 0;
    private int back_pointer = 0;
    private T[] array;
    private int len = 0;

    public Deque(int length) {
        array = (T[]) new Object[length];
        min_capacity = length;
    }

    public Deque() {
        this(10);
    }

    public void rearEnqueue(T element) {
        if(len != 0 && back_pointer == front_pointer) {
            T[] temp = (T[]) new Object[(int) Math.ceil(array.length * GROW_FACTOR)];
            System.arraycopy(array, front_pointer, temp, 0, array.length - front_pointer);
            System.arraycopy(array, 0, temp, array.length - front_pointer, front_pointer);
            back_pointer = len;
            front_pointer = 0;
			array = temp;
        }
        array[back_pointer] = element;
        len++;
        back_pointer = (back_pointer + 1) % array.length;
    }

    public void frontEnqueue(T element) {
        if(len != 0 && back_pointer == front_pointer) {
            T[] temp = (T[]) new Object[(int) Math.ceil(array.length * GROW_FACTOR)];
            System.arraycopy(array, back_pointer, temp, 0, array.length - back_pointer);
            System.arraycopy(array, 0, temp, array.length - back_pointer, back_pointer);
            front_pointer = len;
            back_pointer = 0;
			array = temp;
        }
        if(front_pointer - 1 < 0) {
            front_pointer = array.length - 1;
        }
        else{
            front_pointer = (front_pointer - 1) % array.length;
        }
        array[front_pointer] = element;
        len++;
    }

    public T peekFront() {
        return array[front_pointer];
    }

    public T peekBack() {
        return array[back_pointer];
    }

    public T frontDequeue() {
		T element = array[front_pointer++];
		len--;
        System.out.println(len);
        if(array.length > min_capacity && len <= array.length * SHRINK_LIMIT) {
            T[] temp = (T[]) new Object[(int) Math.ceil(array.length / GROW_FACTOR)];
            if(front_pointer > back_pointer) {
                System.arraycopy(array, front_pointer, temp, 0, len - front_pointer);
                System.arraycopy(array, 0, temp, len - front_pointer, back_pointer);
            }
            else {
                System.arraycopy(array, front_pointer, temp, 0, len);
            }
            array = temp;
            back_pointer = len;
            front_pointer = 0;
        }
        return element;
    }

    public T rearDequeue() {
        if(back_pointer - 1 < 0) {
            back_pointer = array.length - 1;
        }
        else{
            back_pointer = (back_pointer - 1) % array.length;
        }
		T element = array[back_pointer];
		len--;
        System.out.println(len);
        if(array.length > min_capacity && len <= array.length * SHRINK_LIMIT) {
            T[] temp = (T[]) new Object[(int) Math.ceil(array.length / GROW_FACTOR)];
            if(back_pointer > front_pointer) {
                System.arraycopy(array, back_pointer, temp, 0, len - back_pointer);
                System.arraycopy(array, 0, temp, len - back_pointer, front_pointer);
            }
            else {
                System.arraycopy(array, back_pointer, temp, 0, len);
            }
            array = temp;
            back_pointer = 0;
            front_pointer = len;
        }
        return element;
    }

    public int length() {
        return len;
    }

    public boolean isEmpty() {
        return length() == 0;
    }

    public String toString() {
        return String.format("array: %s front_pointer: %s back_pointer: %s", Arrays.toString(array), front_pointer, back_pointer);
    }
}
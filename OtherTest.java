public class OtherTest {
	public static void main(String[] args) {
        /*
		Stack<String> s = new Stack<>(5);
		s.push("Apple");
		s.push("Banana");
		s.push("Cherry");
		System.out.println(s.pop());
		System.out.println(s.pop());
		System.out.println(s);
		s.push("New Thing");
		System.out.println(s);
		s.push("X");
		s.push("Y");
		s.push("Z");
		s.push("Too Big!");
        System.out.println(s);
        s.pop();
        s.pop();
        s.pop();
        s.pop();
        System.out.println(s);
        

        Queue<String> s = new Queue<>(5);
        s.enqueue("Apple");
        s.enqueue("Banana");
        s.enqueue("Cherry");
        System.out.println(s);
        System.out.println(s.dequeue());
        System.out.println(s.dequeue());
        System.out.println(s);
        System.out.println(s.peek());
        s.enqueue("New Thing");
        System.out.println(s);
        s.enqueue("X");
        s.enqueue("Y");
        s.enqueue("Z");
        s.enqueue("woop");
        System.out.println(s);
        s.dequeue();
        s.dequeue();
        s.dequeue();
        s.dequeue();
        System.out.println(s);

        */

        Deque<String> s = new Deque<>(5);
        s.frontEnqueue("Apple");
        s.rearEnqueue("Banana");
        s.frontEnqueue("Cherry");
        System.out.println(s);
        System.out.println(s.frontDequeue());
        System.out.println(s.rearDequeue());
        System.out.println(s);
        System.out.println(s.peekFront());
        s.frontEnqueue("ahahahahaha");
        System.out.println(s);
        /*
        s.enqueue("New Thing");
        System.out.println(s);
        s.enqueue("X");
        s.enqueue("Y");
        s.enqueue("Z");
        s.enqueue("woop");
        System.out.println(s);
        s.dequeue();
        s.dequeue();
        s.dequeue();
        s.dequeue();
        System.out.println(s);
        */
	}
}
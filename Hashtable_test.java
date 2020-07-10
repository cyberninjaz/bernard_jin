public class Hashtable_test {
    public static void main(String[] args) {
        Hashtable<String> h  = new Hashtable<>();
        h.add("Pineapple");
        h.add("Grape");
        h.add("Apple");
        System.out.println(h.contains("Pineapple"));
        h.remove("Pineapple");
        System.out.println(h.contains("Pineapple"));
        h.add("Grape");
        System.out.println(h.size());
        System.out.println(h);
        for(int x = 0; x <= 10000; x += 100) {
            h.add(Integer.toString(x));
        }
        for(int x = 0; x < 500; x += 10) {
            h.remove(Integer.toString(x));
        }
        System.out.println(h);
    }
}
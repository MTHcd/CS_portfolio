public class CharBag {
    private int[] counts; // Stores the counts for each letter
    private int size; // Stores the total number of letters in the bag

    // Default constructor
    public CharBag() {
        counts = new int[27];
        size = 0;
    }

    // Adds a character to the char bag
    public void add(char c) {
        // Convert the character to lowercase
        c = Character.toLowerCase(c);

        // If the character is not an English alphabet letter, convert it to the stop character
        if (c < 'a' || c > 'z') {
            c = LetterSample.STOP;
            counts[26]++;
        }
        else
        // Increment the count for the given character
            counts[c - 'a']++;

        // Increment the total size of the bag
        size++;
    }

    // Removes a character from the char bag
    public void remove(char c) {
        // Convert the character to lowercase
        c = Character.toLowerCase(c);

        int indx=c - 'a';
        // If the character is not an English alphabet letter, convert it to the stop character
        if (c < 'a' || c > 'z') {
            c = LetterSample.STOP;
            indx=26;
        }

        // Decrement the count for the given character, if it is greater than zero
        if (counts[indx] > 0) {
            counts[indx]--;

            // Decrement the total size of the bag
            size--;
        }
    }

    // Returns the count for a given character
    public int getCount(char c) {
        // Convert the character to lowercase
        c = Character.toLowerCase(c);

        // If the character is not an English alphabet letter, convert it to the stop character
        if (c < 'a' || c > 'z') {
            c = LetterSample.STOP;
            return counts[26];
        }

        // Return the count for the given character
        //System.out.println(c - 'a');
        //System.out.println(c);
        return counts[c - 'a'];
    }

    // Returns the total size of the char bag
    public int getSize() {
        return size;
    }

    // Returns a string representation of the char bag
    public String toString() {
        StringBuilder sb = new StringBuilder();

        sb.append("CharBag{");
        // Append the count for each letter to the string
        for (int i = 0; i < 26; i++) {
            sb.append((char) ('a' + i) + ":" + counts[i] + ", ");
        }

        // Append the count for the stop character to the string
        sb.append(LetterSample.STOP + ":" + counts[26]+"}");

        return sb.toString();
    }







    // Returns a randomly chosen char from the char bag
    public char getRandomChar() {
        // Generate a random number between 0 and the total size of the bag
        int index = (int) (Math.random() * size);

        // Iterate through the counts of each character
        for (int i = 0; i < counts.length; i++) {
            // If the index is less than the current character's count, return that character
            if (index < counts[i]) {
                if(i<26)
                    return (char) ('a' + i);
                else
                    return LetterSample.STOP;
            }
            // Otherwise, subtract the current character's count from the index
            else {
                index -= counts[i];
            }
        }

        // If the CharBag is empty, return the stop character
        return LetterSample.STOP;
    }
}
public class Gibberisher {
    private Trie<CharBag> model; // Stores the CharBags for each word segment
    private int segmentLength; // Stores the length of each word segment
    private int sampleCount; // Stores the number of LetterSamples processed

    
    // Constructor that takes the segment length and initializes the Trie and sample count
    public Gibberisher(int segmentLength) {
        this.segmentLength = segmentLength;
        model = new Trie<CharBag>();
        sampleCount = 0;
    }

    // Trains the model with the given array of strings
    public void train(String[] samples) {
        for (String s : samples) {
            // Generate the LetterSamples for the given string
            LetterSample[] lSamples = LetterSample.toSamples(s, segmentLength);

            for (LetterSample lSample : lSamples) {
                // Get the CharBag for the current word segment
                CharBag charBag = model.get(lSample.getSegment());

                // If the CharBag is null, create a new one and add it to the model
                if (charBag == null) {
                    charBag = new CharBag();
                    model.put(lSample.getSegment(), charBag);
                }

                // Add the character from the LetterSample to the CharBag
                char let=lSample.getNextLetter();
                //System.out.println(let);
                charBag.add(let);


                // Increment the sample count
                sampleCount++;
            }
        }
    }

    // Returns the number of distinct LetterSamples processed
    public int getSampleCount() {
        return sampleCount;
    }

    // Generates a random string based on the trained model
    public String generate() {
        StringBuilder sb = new StringBuilder();

        // Generate random words until the stop character is reached
        char c = ' ';
        while (c != LetterSample.STOP) {
            // Get the CharBag for the current word segment
            CharBag charBag = model.get(sb.toString());

            // If the CharBag is null, return the generated string without the stop character
            if (charBag == null) {
                return sb.toString().replace(LetterSample.STOP, ' ').trim();
            }

            // Get a random character from the CharBag
            c = charBag.getRandomChar();

            // Append the character to the generated string
            sb.append(c);
        }

        return sb.toString().replace(LetterSample.STOP, ' ').trim();
    }
}
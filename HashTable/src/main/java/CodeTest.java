/**
 * Homework #3 Same Pattern
 * Unit Test
 */

import org.msgpack.core.MessagePack;
import org.msgpack.core.MessagePacker;
import org.msgpack.core.MessageUnpacker;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.lang.Thread;

public class CodeTest {

public static void main(String[] args) throws Exception {
	// preparing inputs
	final int count = 4;
	final String pattern1 = "xyxy";
	final String sequence1 = "sense lab sense lab";
	final int match1 = 1;
	final String pattern2 = "xyxy";
	final String sequence2 = "sense lab lab sense";
	final int match2 = 0;
	final String pattern3 = "xyxy";
	final String sequence3 = "sense lab sense lab sense";
	final int match3 = 0;
	final String pattern4 = "apple";
	final String sequence4 = "sleep go go no time";
	final int match4 = 1;
	// generating inputs
	String[] seqArray1 = sequence1.split(" ");
	String[] seqArray2 = sequence2.split(" ");
	String[] seqArray3 = sequence3.split(" ");
	String[] seqArray4 = sequence4.split(" ");
	// writing inputs
	MessagePacker packer = MessagePack.newDefaultPacker(new FileOutputStream("input.txt"));
	packer.packInt(count);
	packer.packString(pattern1);
	packer.packArrayHeader(seqArray1.length);
	for (String word : seqArray1)
		packer.packString(word);
	packer.packString(pattern2);
	packer.packArrayHeader(seqArray2.length);
	for (String word : seqArray2)
		packer.packString(word);
	packer.packString(pattern3);
	packer.packArrayHeader(seqArray3.length);
	for (String word : seqArray3)
		packer.packString(word);
	packer.packString(pattern4);
	packer.packArrayHeader(seqArray4.length);
	for (String word : seqArray4)
		packer.packString(word);
	packer.close();
	// running the tests
	Code.main(null);
	// verifying outputs
	MessageUnpacker unpacker = MessagePack.newDefaultUnpacker(new FileInputStream("output.txt"));
	assertEquals(match1, unpacker.unpackInt());
	assertEquals(match2, unpacker.unpackInt());
	assertEquals(match3, unpacker.unpackInt());
	assertEquals(match4, unpacker.unpackInt());
	unpacker.close();
	// exiting the tests
	System.exit(0);
}

private static void assertEquals(int a, int b) {
	int line = Thread.currentThread().getStackTrace()[2].getLineNumber();
	if (a == b)
		System.out.println("Line " + line + ": Test Passed");
	else
		System.out.println("Line " + line + ": Test Failed");
	System.out.println("├─The expected value is " + a + ".");
	System.out.println("└─The actual value is " + b + ".");
	if (a != b)
		System.exit(1);
}

}

/**
 * Unit Test
 */

import org.junit.Test;
import static org.junit.Assert.assertEquals;
import org.msgpack.core.MessagePack;
import org.msgpack.core.MessagePacker;
import org.msgpack.core.MessageUnpacker;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Arrays;
import java.util.concurrent.ThreadLocalRandom;

public class CodeTest {

private int[] dataSet1 = new int[1];
private int[] dataSet2 = new int[25];
private int[] dataSet3 = new int[50];
private int[] dataSet4 = new int[75];
private int[] dataSet5 = new int[100];

@Test
public void mainTest() throws Exception {
	CodeTest codeTest = new CodeTest();
	codeTest.generateInput();
	Code.main(null);
	Arrays.sort(dataSet1);
	Arrays.sort(dataSet2);
	Arrays.sort(dataSet3);
	Arrays.sort(dataSet4);
	Arrays.sort(dataSet5);
	codeTest.verifyOutput();
}

private void generateInput() throws Exception {
	for (int i = 0; i < 1; i++)
		dataSet1[i] = ThreadLocalRandom.current().nextInt();
	for (int i = 0; i < 25; i++)
		dataSet2[i] = ThreadLocalRandom.current().nextInt();
	for (int i = 0; i < 50; i++)
		dataSet3[i] = ThreadLocalRandom.current().nextInt();
	for (int i = 0; i < 75; i++)
		dataSet4[i] = ThreadLocalRandom.current().nextInt();
	for (int i = 0; i < 100; i++)
		dataSet5[i] = ThreadLocalRandom.current().nextInt();
	MessagePacker packer = MessagePack.newDefaultPacker(new FileOutputStream("input.txt"));
	packer.packInt(5);
	packer.packArrayHeader(1);
	for (int i = 0; i < 1; i++)
		packer.packInt(dataSet1[i]);
	packer.packArrayHeader(25);
	for (int i = 0; i < 25; i++)
		packer.packInt(dataSet2[i]);
	packer.packArrayHeader(50);
	for (int i = 0; i < 50; i++)
		packer.packInt(dataSet3[i]);
	packer.packArrayHeader(75);
	for (int i = 0; i < 75; i++)
		packer.packInt(dataSet4[i]);
	packer.packArrayHeader(100);
	for (int i = 0; i < 100; i++)
		packer.packInt(dataSet5[i]);
	packer.close();
}

private void verifyOutput() throws Exception {
	MessageUnpacker unpacker = MessagePack.newDefaultUnpacker(new FileInputStream("output.txt"));
	assertEquals(5, unpacker.unpackInt());
	assertEquals(1, unpacker.unpackArrayHeader());
	for (int i = 0; i < 1; i++)
		assertEquals(dataSet1[i], unpacker.unpackInt());
	assertEquals(25, unpacker.unpackArrayHeader());
	for (int i = 0; i < 25; i++)
		assertEquals(dataSet2[i], unpacker.unpackInt());
	assertEquals(50, unpacker.unpackArrayHeader());
	for (int i = 0; i < 50; i++)
		assertEquals(dataSet3[i], unpacker.unpackInt());
	assertEquals(75, unpacker.unpackArrayHeader());
	for (int i = 0; i < 75; i++)
		assertEquals(dataSet4[i], unpacker.unpackInt());
	assertEquals(100, unpacker.unpackArrayHeader());
	for (int i = 0; i < 100; i++)
		assertEquals(dataSet5[i], unpacker.unpackInt());
	unpacker.close();
}

}

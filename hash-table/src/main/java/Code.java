/**
 * Introduction to Algorithms 2016 Spring
 * Homework #3 Same Pattern
 * by Yu-wen Pwu (rev1)
 */

import org.msgpack.core.MessagePack;
import org.msgpack.core.MessagePacker;
import org.msgpack.core.MessageUnpacker;
import java.io.FileInputStream;
import java.io.FileOutputStream;

public class Code {

private static String[] map = new String[26];

public static void main(String[] args) {
	try {
		MessageUnpacker unpacker = MessagePack.newDefaultUnpacker(new FileInputStream("input.txt"));
		MessagePacker packer = MessagePack.newDefaultPacker(new FileOutputStream("output.txt"));
		int count = unpacker.unpackInt();
		for (int i = 0; i < count; i++) {
			String pattern = unpacker.unpackString();
			int length = pattern.length();
			int wordLength = unpacker.unpackArrayHeader();
			if (wordLength != length) {
				for (int j = 0; j < wordLength; j++)
					unpacker.unpackString();
				packer.packInt(0);
				continue;
			}
			for (int j = 0; j < 26; j++)
				map[j] = null;
			int match = 1;
			for (int j = 0; j < length; j++) {
				int key = pattern.charAt(j) - 'a';
				String value = unpacker.unpackString();
				if (match == 1 && map[key] == null) {
					for (String word : map)
						if (word != null && word.equals(value)) {
							match = 0;
							break;
						}
					map[key] = value;
				}
				else if (match == 1 && !map[key].equals(value))
					match = 0;
			}
			packer.packInt(match);
		}
		unpacker.close();
		packer.close();
	}
	catch (Exception e) {
		e.printStackTrace();
	}
}

}

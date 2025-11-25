module Types;

// REMOVE SWTICH STATEMENTS

BlockType charToBlockType(char ch) {
    switch (ch) {
        case 'I': return BlockType::I;
        case 'J': return BlockType::J;
        case 'L': return BlockType::L;
        case 'O': return BlockType::O;
        case 'S': return BlockType::S;
        case 'Z': return BlockType::Z;
        case 'T': return BlockType::T;
        case '*': return BlockType::Star;
        default:  return BlockType::I;
    }
}

char blockTypeToChar(BlockType t) {
    switch (t) {
        case BlockType::I: return 'I';
        case BlockType::J: return 'J';
        case BlockType::L: return 'L';
        case BlockType::O: return 'O';
        case BlockType::S: return 'S';
        case BlockType::Z: return 'Z';
        case BlockType::T: return 'T';
        case BlockType::Star: return '*';
    }
    return '?';
}

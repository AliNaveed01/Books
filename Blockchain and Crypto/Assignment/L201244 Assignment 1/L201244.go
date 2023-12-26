package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// Block
type Block struct {
	transactions []string
	prevPointer  *Block
	prevHash     string
	currentHash  string
}

func CalculateHash(inputBlock *Block) string {
	// Calculate Hash of a Block
	hash := sha256.New()
	//hash.Write([]byte(inputBlock.currentHash))
	hash.Write([]byte(inputBlock.prevHash))
	for _, transaction := range inputBlock.transactions {
		hash.Write([]byte(transaction))
	}
	return hex.EncodeToString(hash.Sum(nil))
}

func InsertBlock(transactionsToInsert []string, chainHead *Block) *Block {
	// Insert new block and return head pointer
	newBlock := &Block{
		transactions: transactionsToInsert,
		prevPointer:  chainHead,
		prevHash:     chainHead.currentHash,
		currentHash:  "",
	}
	newBlock.currentHash = CalculateHash(newBlock)
	return newBlock
}

func ChangeBlock(oldTrans string, newTrans string, chainHead *Block) {
	for chainHead != nil {
		for i, transaction := range chainHead.transactions {
			if transaction == oldTrans {
				chainHead.transactions[i] = newTrans
				chainHead.currentHash = CalculateHash(chainHead)
				return
			}
		}
		chainHead = chainHead.prevPointer
	}
}

func ListBlocks(chainHead *Block) {
	// Display the data (transactions) inside all blocks
	for i := 0; i < len(chainHead.transactions); i++ {
		fmt.Println(chainHead.transactions[i])
		fmt.Println("Block hash: ", chainHead.currentHash)
	}
}

func VerifyChain(chainHead *Block) {
	for chainHead.prevPointer != nil {
		if chainHead.prevHash != chainHead.prevPointer.currentHash {
			fmt.Println("Blockchain is invalid!")
			return
		}
		chainHead = chainHead.prevPointer

	}
	fmt.Println("Blockchain is valid!")
}

func main() {
	// Create a blockchain
	blockChain := &Block{
		transactions: []string{"Alice sends 5 bitcoins to Bob", "Bob sends 3 bitcoins to Carol", "Dave sends 2 bitcoins to Alice"},
		prevPointer:  nil,
		prevHash:     "",
		// calculate hash of current block
		currentHash: "",
	}
	// Display the initial blockchain
	fmt.Println("Initial Blockchain:")
	ListBlocks(blockChain)
	fmt.Println("") // Display the initial blockchain

	//change a transaction in a block
	ChangeBlock("Bob sends 3 bitcoins to Carol", "Bob sends 1 bitcoin to Carol", blockChain)
	// Display the updated blockchain

	fmt.Println("Updated Blockchain after inserting a new block:")
	ListBlocks(blockChain)
	fmt.Println("")

	//check the integrity of the blockchain
	VerifyChain(blockChain)

	// insert a new block
	blockChain = InsertBlock([]string{"Eve sends 7 bitcoins to Frank"}, blockChain)
	// Display the updated blockchain
	fmt.Println("Updated Blockchain after inserting a new block:")
	ListBlocks(blockChain)
	fmt.Println("")
}

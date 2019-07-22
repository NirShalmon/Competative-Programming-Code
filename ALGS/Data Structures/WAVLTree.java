/**
 *
 * WAVLTree
 *
 * An implementation of a WAVL Tree with
 * distinct integer keys and info
 */

public class WAVLTree {
	
	WAVLNode root;
	WAVLNode min; 
	WAVLNode max;
	
  /**
   * public boolean empty()
   *
   * returns true if and only if the tree is empty
   * time: O(1)
   */
	public boolean empty() {
		return root == null;
   }
	/**
	 * private WAVLNode treePosition(int k)
	 * 
	 * returns the WAVLNode where key k belongs in tree:
	 * if a node containing key k exists returns said node
	 * if it doesn't exist, returns the virtual node where this key should be in the binary tree
	 * returns null if tree is empty
	 * time: O(logn)
	 */
	private WAVLNode treePosition(int k){
		if(empty()){
		   return null;
		}
		IWAVLNode node = root;
		while(node.isRealNode() && node.getKey() != k){ //while we havn't found k and we are still have children to look through
			if(k < node.getKey()){	//direction dictated by the binary search tree property
			   node = node.getLeft();
			}else{
			   node = node.getRight();
			}
		}
		return (WAVLNode)node;
	}

 /**
   * public String search(int k)
   *
   * returns the info of an item with key k if it exists in the tree
   * otherwise, returns null
   * time: O(logn)
   */
   public String search(int k)
   {
	   WAVLNode node = treePosition(k);
	   if(node == null || !node.isRealNode()){ //if k is not in the tree
		   return null;
	   }
	   return node.getValue();
   }

   /**
    * private void rotate(WAVLNode child)
    * 
    * precondition: child.getParent() != null && child.isRealNode()
    * performs a tree rotation with child and it's parent
    * determines whether to do a right/left rotation based on which son of child's parent child is
    * time: O(1)
    */
   private void rotate(WAVLNode child){
	   WAVLNode parent = (WAVLNode)child.getParent();
	   boolean rightRotation = (child == parent.getLeft()); //is this a right rotation?
	   if(parent.getParent() != null){ //fix the parent of parent
		   if(parent.getParent().getLeft() == parent){
			   ((WAVLNode)parent.getParent()).setLeft(child);
		   }else{
			   ((WAVLNode)parent.getParent()).setRight(child);
		   }
	   }
	   ((WAVLNode)child.getChild(!rightRotation)).setParent(parent);
	   parent.setChild(child.getChild(!rightRotation),rightRotation);
	   child.setParent(parent.getParent());
	   parent.setParent(child);
	   child.setChild(parent,!rightRotation);
	   if(parent == root){ //did we change the root?
		   root = child;
	   }
	   parent.updateSubtreeSize();
	   child.updateSubtreeSize();
   }
   /**
    * private int rebalanceInsert(WAVLNode z)
    * 
    * rebalances tree after an insert operation from node z upwards
    * stops when node is a valid WAVLNode and tree is fixed 
    * returns the number of rebalancing actions performed
    * time: O(logn)
    */
   private int rebalanceInsert(WAVLNode z){
	   if(z == null){
		   return 0;
	   }
	   if(z.isValidNode()){ //z is balanced
		   return 0;
	   }
	   //if this is a 1-0 node or a 0-1 node
	   if(z.getRank() == ((WAVLNode)z.getLeft()).getRank() && z.getRank() == ((WAVLNode)z.getRight()).getRank() + 1 || 
			   z.getRank() == ((WAVLNode)z.getLeft()).getRank() +1 && z.getRank() == ((WAVLNode)z.getRight()).getRank()){
		   z.premote();
		   return rebalanceInsert((WAVLNode)z.getParent()) + 1; //problem might be moved up
	   }
	   //we know that it is a 2-0 or 0-2 node
	   //is this 0-2?
	   boolean zeroEdgeIsLeft = z.getRank() == ((WAVLNode)z.getLeft()).getRank();
	   WAVLNode x = (WAVLNode)z.getChild(zeroEdgeIsLeft); //the node below the 0 edge
	   if(((WAVLNode)x.getChild(zeroEdgeIsLeft)).getRank() == x.getRank() - 1){ //case 2 from the presentation
		   rotate(x);
		   z.demote();
		   return 2;
	   }else{//case 3 from the presentation
		   WAVLNode b = (WAVLNode)x.getChild(!zeroEdgeIsLeft); //the node below the 2 edge of z
		   rotate(b);
		   rotate(b);
		   x.demote();
		   z.demote();
		   b.premote();
		   return 5;
	   }
   }
   /**
    * private void updateSubtreeSizes(WAVLNode node)
    * 
    * updates SubtreeSize field for node z and its ancestors in the tree, going upwards
    * time: O(logn)
    */
   private void updateSubtreeSizes(WAVLNode node){
		while(node != null){
			  node.updateSubtreeSize();
			  node = (WAVLNode)node.getParent();
		}
   }
   
  /**
   * public int insert(int k, String i)
   *
   * inserts an item with key k and info i to the WAVL tree.
   * the tree must remain valid (keep its invariants).
   * returns the number of rebalancing operations, or 0 if no rebalancing operations were necessary.
   * returns -1 if an item with key k already exists in the tree.
   * time: O(logn)
   */
   public int insert(int k, String i) {
	  if(empty()){
		  root = new WAVLNode(k,i,null);
		  min = root;
		  max = root;
		  return 0; // rebalancing done
	  }
	  //tree insert
	  WAVLNode y = treePosition(k);
	  if(k == y.getKey()){ //if k is already in the tree
		  return -1;
	  }
	  y = (WAVLNode)y.getParent(); //the node that we should insert below
	  WAVLNode z = new WAVLNode(k,i,y); //our new node
	  if(min.getKey()>k)
	  {
		  min = z;
	  }
	  if(max.getKey()<k)
	  {
		  max = z;
	  }
	  boolean wasLeaf = y.isLeaf();
	  if(z.getKey() < y.getKey()){ //direction dictated by the binary search tree property
		  y.setLeft(z);
	  }else{
		  y.setRight(z);
	  }
	  updateSubtreeSizes(y);
	  if(wasLeaf){
		  //rebalancing might be needed
		  return rebalanceInsert(y);
	  }
	  return 0; //no rebalancing was needed
   }
   
   /**
    * private int rebalanceDelete(WAVLNode z)
    * 
    * rebalances tree after a delete operation from node z upwards
    * stops when node is a valid WAVLNode and tree is fixed 
    * returns the number of rebalancing actions performed
    * time: O(logn)
    */
   private int rebalanceDelete(WAVLNode z){
	   if(z == null){ 
		   return 0;
	   }
	   if(z.isValidNode()){ //no rebalancing needed
		   return 0;
	   }
	   //we know that z is a 3-2 2-3 3-1 or 1-3 node
	   boolean threeEdgeIsLeft = z.getRank() - ((WAVLNode)z.getLeft()).getRank() == 3; //is z a 3-x node?
	   WAVLNode y = (WAVLNode)z.getChild(!threeEdgeIsLeft); // the node below the 2 or 1 edge
	   if(z.getRank() - ((WAVLNode)z.getChild(!threeEdgeIsLeft)).getRank() == 2){ //if z is 2-3 or 3-2
		   //case 1
		   z.demote();
		   return rebalanceDelete((WAVLNode)z.getParent()) + 1; //problem might be moved up
	   }else if(y.getRank() - ((WAVLNode)y.getLeft()).getRank() == 2 && y.getRank() - ((WAVLNode)y.getRight()).getRank() == 2){ //if y is a 2-2 node
		   //case 2
		   z.demote();
		   y.demote();
		   return 2 + rebalanceDelete((WAVLNode)z.getParent()); //problem might be pushed up
	   }else if(y.getRank() - ((WAVLNode)y.getChild(!threeEdgeIsLeft)).getRank() == 1){ //case 3 from the presentation
		   //case 3
		   z.demote();
		   y.premote();
		   rotate(y);
		   if(z.getRank() - ((WAVLNode)z.getLeft()).getRank() == 2 && z.getRank() - ((WAVLNode)z.getRight()).getRank() == 2){ //subcase of case 3 from the presentation, when y is a 1-1 node
			   z.demote();
			   return 4;
		   }
		   return 3;
	   }else{
		   //case 4
		   WAVLNode a = (WAVLNode)y.getChild(threeEdgeIsLeft); //the node below the 1 edge of y
		   rotate(a);
		   rotate(a);
		   z.demote();
		   z.demote();
		   y.demote();
		   a.premote();
		   a.premote();
		   return 7;
	   }
   }
   
  /**
   * public int delete(int k)
   *
   * deletes an item with key k from the binary tree, if it is there;
   * the tree must remain valid (keep its invariants).
   * returns the number of rebalancing operations, or 0 if no rebalancing operations were needed.
   * returns -1 if an item with key k was not found in the tree.
   * time: O(logn)
   */
   public int delete(int k)
   {
	   if(empty()){
		   return -1; //k is not in an empty tree
	   }
	   WAVLNode y = treePosition(k); //the node of k(if one exists)
	   if(!y.isRealNode()){
		   return -1; //no real node matched k
	   }
	   WAVLNode parent = (WAVLNode)y.getParent();
	   if(y.getLeft().isRealNode() && y.getRight().isRealNode()){ //both of y's children are real
		   WAVLNode succ = (WAVLNode)successor(y); //y's successor will take y's position and y will be erased 
		   if(y == root){
			   root = succ; //succ takes y's position
		   }
		   //bypass the successor node(which is unary)
		   //parent is the parent of the node to be erased
		   if(succ.getParent() == y){ //special case for when y is the parent of it's successor
			   y.setRight(succ.getRight());
			   parent = succ;
		   }else{
			   parent = (WAVLNode)succ.getParent();
			   if(succ == succ.getParent().getLeft()){ //replace the child of the bypassed node's parent
				   ((WAVLNode)succ.getParent()).setLeft(succ.getRight());
			   }else{
				   ((WAVLNode)succ.getParent()).setRight(succ.getRight());
			   }
			   ((WAVLNode)succ.getRight()).setParent(succ.getParent());//replace the parent of the bypassed node's only real child
		   }
		   succ.imitate(y);
		   updateSubtreeSizes(parent);
		   if(k==min.getKey())
		   {
			   min = min(root);
		   }
		     if(k==max.getKey())
		   {
			   max = max(root);
		   }
		   if(parent.isLeaf() && parent.getRank() == 1){ //special case (from the presentation) when deleting a leaf that is a child of an unary node
			   parent.demote();
			   return rebalanceDelete((WAVLNode)parent.getParent()) + 1;
		   }
		   return rebalanceDelete(parent);
	   }
	   if(y.isLeaf()){
		   if(y == root){
			   root = null; //the root was a leaf, meaning that the tree only contained k
			   min = null;
			   max = null;
			   return 0;
		   }
		   if(parent.getLeft() == y){ //put an unreal node in y's position
			   parent.setLeft(new WAVLNode(parent));
		   }else{
			   parent.setRight(new WAVLNode(parent));
		   }
		   updateSubtreeSizes(parent);
		   if(k==min.getKey())
		   {
			   min = min(root);
		   }
		     if(k==max.getKey())
		   {
			   max = max(root);
		   }
		   if(parent.isLeaf()){ //special case (from the presentation) when deleting a leaf that is a child of an unary node
			   parent.demote();
			   return rebalanceDelete((WAVLNode)parent.getParent());
		   }else{
			   return rebalanceDelete(parent);
		   }
	   }else{ //deleting an unary node
		   //boolean yIsParentLeftChild = y == parent.getLeft();
		   //connect the real child of y to y's parent, 
		   //or if y is root than the new tree is just the subtree of y in the direction of the real node
		   if(!y.getLeft().isRealNode()){
			   ((WAVLNode)y.getRight()).setParent(parent); 
			   if(y == root){
				   root = (WAVLNode)y.getRight();
				   if(k==min.getKey())
				   {
					   min = min(root);
				   }
				   return 0;
			   }
			   parent.setChild(y.getRight(), y == parent.getLeft());
		   }else if(!y.getRight().isRealNode()){
			   ((WAVLNode)y.getLeft()).setParent(parent);
			   if(y == root){
				   root = (WAVLNode)y.getLeft();
				     if(k==max.getKey())
				   {
					   max = max(root);
				   }
				   return 0;
			   }
			   parent.setChild(y.getLeft(), y == parent.getLeft());
		   }
		   updateSubtreeSizes(parent);
		   if(k==min.getKey())
		   {
			   min = min(root);
		   }
		     if(k==max.getKey())
		   {
			   max = max(root);
		   }
		   return rebalanceDelete(parent);
	   }
   }
   /**
    * private WAVLNode successor(WAVLNode node)
    * 
    * returns node's successor in tree if it exists
    * returns null if it doesn't i.e. node has the maximum key 
    * time: O(logn)
    */
   private WAVLNode successor(WAVLNode node){
	   if(node.getRight().isRealNode()){ //if there is a real right child return the min of it's subtree
		   return min((WAVLNode)node.getRight());
	   }
	   while(node.getParent() != null && node.getParent().getRight() != node){ //go up until the first turn right
		   node = (WAVLNode)node.getParent();
	   }
	   return (WAVLNode)node.getParent(); //will be null if node was originaly the maximum
   }
   
   /**
    * public String min()
    *
    * Returns the info of the item with the smallest key in the tree,
    * or null if the tree is empty
    * time: O(1)
    */
   public String min()
   {
	   if(empty()){ //an empty tree has no maximum
		   return null;
	   }
	   return min.getValue();
   }
  
   /**
    * private WAVLNode min(WAVLNode node)
    * 
    * returns the node with the smallest key in node's subtree
    * time: O(logn)
    */
   private WAVLNode min(WAVLNode node){
	   if(node.getLeft().isRealNode()){ //recursively go left until the last real node
		   return min((WAVLNode)node.getLeft());
	   }
	   return node;
   }
   
   /**
    * private WAVLNode max(WAVLNode node)
    * 
    * returns the node with the largest key in node's subtree
    * time: O(logn)
    */
   private WAVLNode max(WAVLNode node){
	   if(node.getRight().isRealNode()){ //recursively go right until the last real node
		   return max((WAVLNode)node.getRight());
	   }
	   return node;
   }

   /**
    * public String max()
    *
    * Returns the info of the item with the largest key in the tree,
    * or null if the tree is empty
    * time: O(1)
    */
   public String max()
   {
	   if(empty()){ //an empty tree has no maximum
		   return null;
	   }
	   return max.getValue();
   }
   
   /**
    * private String[] join(String[] left, String mid, String[] right)
    * 
    * left,right != null
    * returns  (Left.concatenate([mid])).concatenate(right)
    * time: O(left.length + 1 + right.length)
   */
   private String[] join(String[] left, String mid, String[] right){
	   String[] ans = new String[left.length + 1 + right.length];
	   for(int i = 0; i < left.length; ++i){
		   ans[i] = left[i]; //first the elements from left
	   }
	   ans[left.length] = mid; //than mid
	   for(int i = 0; i < right.length; ++i){
		   ans[i + left.length + 1] = right[i]; //finally the elements from right
	   }
	   return ans;
   }
   
   /**
    * private int[] join(int[] left, int mid, int[] right)
    * 
    * left,right != null
    * returns (Left.concatenate([mid])).concatenate(right)
    * time: O(left.length + 1 + right.length)
   */
   private int[] join(int[] left, int mid, int[] right){
	   int[] ans = new int[left.length + 1 + right.length];
	   for(int i = 0; i < left.length; ++i){
		   ans[i] = left[i]; //first the elements from left
	   }
	   ans[left.length] = mid; //then mid
	   for(int i = 0; i < right.length; ++i){
		   ans[i + left.length + 1] = right[i]; //finally the elements from right
	   }
	   return ans;
   }
   
  /**
   * public int[] keysToArray()
   *
   * Returns a sorted array which contains all keys in the tree,
   * or an empty array if the tree is empty.
   * time: O(n)
   */
  public int[] keysToArray()
  {
	  return keysToArray(root); //the subtree of root is the whole tree
  }
  
  /**
   *  private int[] keysToArray(IWAVLNode node)
   *  
   * Returns a sorted array which contains all keys in the node's subtree,
   * time: O(k) where k is the size of node's subtree, O(n) worst-case
   */
  private int[] keysToArray(IWAVLNode node){
	  if(!node.isRealNode()){
		  return new int[0];
	  }
	  return join(keysToArray(node.getLeft()),node.getKey(),keysToArray(node.getRight())); //in order scan
  }

  /**
   * public String[] infoToArray()
   *
   * Returns an array which contains all info in the tree,
   * sorted by their respective keys,
   * or an empty array if the tree is empty.
   * time: O(n)
   */
  public String[] infoToArray()
  {
	  return infoToArray(root);
  }
  
  /**
   * private String[] infoToArray(IWAVLNode node)
   * 
   * Returns an array which contains all info in node's subtree,
   * sorted by their respective keys,
   * or an empty array if the tree is empty.
   * time: O(k) where k is the size of node's subtree, O(n) worst-case
   */
  private String[] infoToArray(IWAVLNode node){
	  if(!node.isRealNode()){
		  return new String[0];
	  }
	  return join(infoToArray(node.getLeft()),node.getValue(),infoToArray(node.getRight())); //in order scan
  }

   /**
    * public int size()
    *
    * Returns the number of nodes in the tree.
    */
   public int size()
   {
	   if(empty()){
		   return 0;
	   }
	   return root.getSubtreeSize(); //the subtree of the root is the whole tree
   }
   
     /**
    * public int getRoot()
    *
    * Returns the root WAVL node, or null if the tree is empty
    *
    * precondition: none
    * postcondition: none
    */
   public IWAVLNode getRoot()
   {
	   return root;
   }
     /**
    * public int select(int i)
    *
    * Returns the value of the i'th smallest key (return -1 if tree is empty)
    * Example 1: select(1) returns the value of the node with minimal key 
	* Example 2: select(size()) returns the value of the node with maximal key 
	* Example 3: select(2) returns the value 2nd smallest minimal node, i.e the value of the node minimal node's successor 	
    *
	* precondition: size() >= i > 0
    * postcondition: none
    * Time: O(logn)
    */   
   public String select(int i)
   {
	   if(empty()){
		   return null;
	   }
	   --i; //start counting at 0
	   IWAVLNode node = root;
	   while(i >= 0){
		   if(node.getLeft().getSubtreeSize() > i){ //if the left subtree of node is large enough to contain an i'th element
			   node = node.getLeft();
		   }else if(node.getLeft().getSubtreeSize() == i){ //if the i'th element in node's subtree is node
			   return node.getValue();
		   }else{
			   i -= node.getLeft().getSubtreeSize() + 1; //we skip this many elements when going right
			   node = node.getRight();   
		   }
	   }
	   return null; //this will never happen
   }

	/**
	   * public interface IWAVLNode
	   * ! Do not delete or modify this - otherwise all tests will fail !
	   */
	public interface IWAVLNode{	
		public int getKey(); //returns node's key (for virtuval node return -1)
		public String getValue(); //returns node's value [info] (for virtuval node return null)
		public IWAVLNode getLeft(); //returns left child (if there is no left child return null)
		public IWAVLNode getRight(); //returns right child (if there is no right child return null)
		public boolean isRealNode(); // Returns True if this is a non-virtual WAVL node (i.e not a virtual leaf or a sentinal)
		public int getSubtreeSize(); // Returns the number of real nodes in this node's subtree (Should be implemented in O(1))
	}

   /**
   * public class WAVLNode
   *
   * If you wish to implement classes other than WAVLTree
   * (for example WAVLNode), do it in this file, not in 
   * another file.
   * This class can and must be modified.
   * (It must implement IWAVLNode)
   */
  public class WAVLNode implements IWAVLNode{
	    private int key;
	    private String value;
	    private IWAVLNode left;
	    private IWAVLNode right;
	    private boolean realNode;
		private int subtreeSize;
		private IWAVLNode parent;
		private int rank;
		
		public WAVLNode(int key, String value, WAVLNode parent){
			this.parent = parent;
			this.key = key;
			this.value = value;
			realNode = true;
			left = new WAVLNode(this);
			right = new WAVLNode(this);
			subtreeSize = 1;
		}
		
		public WAVLNode(WAVLNode parent){
			rank = -1;
			key = -1;
			this.parent = parent;
		}
		
		public void updateSubtreeSize(){
			subtreeSize = left.getSubtreeSize() + right.getSubtreeSize() + 1;
		}
		
		public void setLeft(IWAVLNode left){
			this.left = left;
		}
		
		public void setRight(IWAVLNode right){
			this.right = right;
		}
		
		public void setChild(IWAVLNode child,boolean isLeft){
			if(isLeft){
				setLeft(child);
			}else{
				setRight(child);
			}
		}
		
		public IWAVLNode getChild(boolean isLeft){
			if(isLeft){
				return getLeft();
			}
			return getRight();
		}
		
		public void setParent(IWAVLNode parent){
			this.parent = parent;
		}
		
		//assumes isRealNode()
		public boolean isLeaf(){
			return !(left.isRealNode() || right.isRealNode());
		}
		
		public int getKey()
		{
			return key;
		}
		public String getValue()
		{
			return value;
		}
		public IWAVLNode getLeft()
		{
			return left;
		}
		public IWAVLNode getRight()
		{
			return right;
		}
		// Returns True if this is a non-virtual WAVL node (i.e not a virtual leaf or a sentinal)
		public boolean isRealNode()
		{
			return realNode;
		}

		public int getSubtreeSize()
		{
			return subtreeSize;
		}
		
		public IWAVLNode getParent(){
			return parent;
		}
		
		public void premote(){
			rank++;
		}
		
		public void demote(){
			rank--;
		}
		
		public int getRank(){
			return rank;
		}
		
		/**
		 * public void imitate(WAVLNode b){
		 * 
		 * this node "replaces" b, gets its children, parents, rank and subtree size
		 * also sets the appropriate pointers pointing to b, to this node
		 * time: O(1)
		 */
		public void imitate(WAVLNode b){
			//set the nodes pointers to b's pointers
			left = b.left;
			right = b.right;
			parent = b.parent;
			//set the pointers pointing at b to this
			((WAVLNode)left).parent = this;
			((WAVLNode)right).parent = this;
			if(parent != null){
				if(parent.getLeft() == b){
					((WAVLNode)parent).setLeft(this);
				}else{
					((WAVLNode)parent).setRight(this);
				}
			}
			//copy b's rank and subtree size
			rank = b.rank;
			subtreeSize = b.subtreeSize;
		}
		
		/**
		 * public boolean isValidNode(){
		 * 
		 * checks whether a node is a legal WAVL node i.e. the difference in ranks are valid
		 * returns true if the rank differences are suitable for a WAVLNode and false otherwise
		 * time: O(1)
		 */
		public boolean isValidNode(){
			if(rank - ((WAVLNode)left).rank != 1 && rank - ((WAVLNode)left).rank != 2){
				return false; //the left edge is not a 1 or a 2 edge
			}
			if(rank - ((WAVLNode)right).rank != 1 && rank - ((WAVLNode)right).rank != 2){
				return false; //the right edge is not a 1 or a 2 edge
			}
			return true;
		}
  }

}
  


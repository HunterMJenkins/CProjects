import json
import requests
from bs4 import BeautifulSoup

# Read in the file
def read_ast_from_file(file_path):
    with open(file_path, 'r') as file:
        return json.load(file)
    
def collect_imports(imports, collected_nodes):
     # Collect imports from the imports key
    if 'Imports' not in collected_nodes:
        collected_nodes['Imports'] = []
    for import_decl in imports:
        collected_nodes['Imports'].append(import_decl['path'])

## Traverse and Collect Nodes
def traverse_and_collect_nodes(node, collected_nodes, parent=None):
    node_type = node.get('type')

    # Directly append the node information to the respective list based on node type
    if node_type == 'ClassDeclaration' or node_type == 'InterfaceDeclaration':
        if 'Classes' not in collected_nodes:
            collected_nodes['Classes'] = []
        collected_nodes['Classes'].append(node.get('name'))
    elif node_type == 'MethodDeclaration':
        if 'Methods' not in collected_nodes:
            collected_nodes['Methods'] = []
        collected_nodes['Methods'].append(node.get('name'))
    elif node_type in ['VariableDeclarator', 'FieldDeclaration']:
        if 'Variables' not in collected_nodes:
            collected_nodes['Variables'] = []
        collected_nodes['Variables'].append(node.get('name'))
    elif node_type in ['Literal', 'StringLiteral', 'NumberLiteral', 'BooleanLiteral']:
        if 'Literals' not in collected_nodes:
            collected_nodes['Literals'] = []
        collected_nodes['Literals'].append(node.get('value'))
    # Add additional conditions for other node types as needed

    # Recursively process child nodes
    for key, value in node.items():
        if isinstance(value, dict):
            traverse_and_collect_nodes(value, collected_nodes, node)
        elif isinstance(value, list):
            for item in value:
                if isinstance(item, dict):
                    traverse_and_collect_nodes(item, collected_nodes, node)

def get_java(imports):
    # Construct the URL to the official Java documentation page for the class
    base_url = "https://docs.oracle.com/javase/8/docs/api/"
    urls = []

    for import_decl in imports:
        class_path = import_decl.replace('.', '/') + ".html"
        ## print (class_path)
        url = base_url + class_path
        urls.append(url)
    
    return urls

# Parsing function using Beautiful Soup
def parse_java_doc(url):
    response = requests.get(url)
    if response.status_code == 200:

        soup = BeautifulSoup(response.text, 'html.parser')
        
        # Extract the title of the page
        title = soup.find('title').text
        print(f"Title of the page: {title}")

        # Extract the class description for each one
        description = soup.find('div', class_='description')
        if description:
            para = description.find('p')
            if para:
                print(f"Class Description: {para.text}")


    else:
        print(f"Failed to fetch the page: {url}")

#-----------------------------------------------------------------------------------------

def main():
    ast_file_path = 'ast.json'  # Replace with your actual file path

    # Read the AST from the JSON file
    ast = read_ast_from_file(ast_file_path)

    # Initialize a dictionary to collect nodes by category
    collected_nodes = {}

    # Traverse the AST and collect nodes
    traverse_and_collect_nodes(ast, collected_nodes)
    # Collect imports directly from the 'imports' key in the AST
    if 'imports' in ast:
        collected_nodes['Imports'] = [import_decl['path'] for import_decl in ast['imports']]


    # Traverse the AST and collect nodes, assuming 'types' key contains the nodes
    if 'types' in ast:
        for type_node in ast['types']:
            traverse_and_collect_nodes(type_node, collected_nodes)
    
    # Print the collected nodes, organized by category
    for category, names in collected_nodes.items():   
        print(f"{category}: {names}")

    # Call get_java with the collected imports
    if 'Imports' in collected_nodes:
        urls = get_java(collected_nodes['Imports'])
        print(urls)

        # Iterate over each URL and parse the Java documentation page
        for url in urls:
            parse_java_doc(url)

if __name__ == '__main__':
    main()

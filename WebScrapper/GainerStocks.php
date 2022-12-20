<?php
// Connect to MongoDB
$m = new MongoDB\Driver\Manager("mongodb://localhost:27017");

// Query the top 5 Documents
$query = new MongoDB\Driver\Query([], ['limit' => 5]);

// Execute the query
$cursor = $m->executeQuery('Stocks.stocks', $query);

?>
<div>
    <!-- HTML TABLE -->
    <table>
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Price</th>
            <th>Change</th>
            <th>Volume</th>
        </tr>
        <?php foreach ($cursor as $document) { ?>
            <tr>
                <td><?php echo $document->Symbol; ?></td>
                <td><?php echo $document->Name; ?></td>
                <td><?php echo $document->Price; ?></td>
                <td><?php echo $document->Change; ?></td>
                <td><?php echo $document->Volume; ?></td>
            </tr>
        <?php } ?>
    </table>
</div>
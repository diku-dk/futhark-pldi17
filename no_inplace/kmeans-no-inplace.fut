-- Hacked-up kmeans without in-place updates.
--
-- ==
-- input @ data/kdd_cup.in
-- output @ data/kdd_cup.out

fun euclid_dist_2 (pt1: [numdims]f32) (pt2: [numdims]f32): f32 =
  reduce (+) 0.0f32 (map (**2.0f32) (map (-) pt1 pt2))

fun closest_point (p1: (i32,f32)) (p2: (i32,f32)): (i32,f32) =
  if #1 p1 < #1 p2 then p1 else p2

fun find_nearest_point(pts: [k][d]f32) (pt: [d]f32): i32 =
  let (i, _) = reduceComm closest_point (0, euclid_dist_2 pt pts[0])
               (zip (iota k) (map (euclid_dist_2 pt) pts))
  in i

fun add_centroids(x: [d]f32) (y: [d]f32): *[d]f32 =
  map (+) x y

fun centroids_of(k: i32, points: [n][d]f32, membership: [n]i32): *[k][d]f32 =
  let counts_increments = map (\i ->
                               unsafe
                               let a = replicate k 0
                               let a[i] = 1
                               in a) membership
  let cluster_sizes = map (\x -> reduce (+) 0 x) (transpose counts_increments)

  let sums_increments = map (\p c ->
                             unsafe
                             let a = replicate k (replicate d 0.0f32)
                             let a[c] = map (/(f32(cluster_sizes[c]))) p
                             in a)
                            points membership
  let cluster_sums = map (\x -> map (\y -> reduce (+) 0.0f32 y) x)
                    (rearrange (1,2,0) sums_increments)
  in cluster_sums

fun main(threshold: i32, k: i32, max_iterations: i32,
         points: [n][d]f32): ([][]f32, i32) =
  -- Assign arbitrary initial cluster centres.
  let cluster_centres = map (\(i: i32): [d]f32  ->
                               unsafe points[i])
                            (iota k)
  -- Also assign points arbitrarily to clusters.
  let membership = map (%k) (iota n)
  let delta = threshold + 1
  let i = 0
  loop ((membership, cluster_centres, delta, i)) =
    while delta > threshold && i < max_iterations do
      -- For each point, find the cluster with the closest centroid.
      let new_membership = map (find_nearest_point cluster_centres) points
      -- Then, find the new centres of the clusters.
      let new_centres = centroids_of(k, points, new_membership)
      let delta = reduce (+) 0 (map (\(b: bool): i32  ->
                                       if b then 0 else 1)
                                (map (==) membership new_membership))
      in (new_membership, new_centres, delta, i+1)
  in (cluster_centres, i)
